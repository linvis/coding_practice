/*
 * File name: simple_mod.c
 */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/kfifo.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/poll.h>

/*
 * mknod /dev/buffer_char0 c 252 0
 * mknod /dev/buffer_char1 c 252 1
 */

#define MAX_DEVICE_BUFFER_SIZE 64
#define DEMO_NAME "buffer_char"
#define MYDEMO_FIFO_SIZE 64

static dev_t dev;
static struct cdev *demo_cdev;

struct mydemo_device_t {
    char name[64];
    struct device *dev;
    wait_queue_head_t read_queue;
    wait_queue_head_t write_queue;
    struct kfifo mydemo_fifo;
};

struct mydemo_private_data {
    struct mydemo_device_t *device;
    char name[64];
};

#define MYDEMO_MAX_DEVICES  8
static struct mydemo_device_t *mydemo_device[MYDEMO_MAX_DEVICES]; 

static int buffer_char_open(struct inode *inode, struct file *file)
{
    unsigned int minor = iminor(inode);
    struct mydemo_private_data *data;
    struct mydemo_device_t *device = mydemo_device[minor];

	printk("%s: major=%d, minor=%d, device=%s\n", __func__, 
			MAJOR(inode->i_rdev), MINOR(inode->i_rdev), device->name);

    data = kmalloc(sizeof(struct mydemo_private_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

	sprintf(data->name, "private_data_%d", minor);

    data->device = device;
    file->private_data = data;

    return 0;
}

static int buffer_char_release(struct inode *inode, struct file *file)
{
    struct mydemo_private_data *data = file->private_data;

    kfree(data);

    return 0;
}

static ssize_t
buffer_char_read(struct file *file, char __user *buf, size_t count,
        loff_t *f_pos)
{
    int actual_readed;
    int ret;
    struct mydemo_private_data *data = file->private_data;
    struct mydemo_device_t *device = data->device;

    if (kfifo_is_empty(&device->mydemo_fifo)) {
        if (file->f_flags & O_NONBLOCK)
            return -EAGAIN;

		printk("%s:%s pid=%d, going to sleep, %s\n", __func__, device->name, current->pid, data->name);
		ret = wait_event_interruptible(device->read_queue,
					!kfifo_is_empty(&device->mydemo_fifo));
        if (ret)
            return ret;

    }

	ret = kfifo_to_user(&device->mydemo_fifo, buf, count, &actual_readed);
    if (ret)
        return -EIO;

	if (!kfifo_is_full(&device->mydemo_fifo))
		wake_up_interruptible(&device->write_queue);

	printk("%s:%s, pid=%d, actual_readed=%d, pos=%lld\n",__func__,
			device->name, current->pid, actual_readed, *f_pos);

    return actual_readed;
}

static ssize_t
buffer_char_write(struct file *file, const char __user *buf, size_t count,
        loff_t *f_pos)
{
    int actual_write;
    int ret;
	struct mydemo_private_data *data = file->private_data;
	struct mydemo_device_t *device = data->device;

	if (kfifo_is_full(&device->mydemo_fifo)){
		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;

		printk("%s:%s pid=%d, going to sleep\n", __func__, device->name, current->pid);
        ret = wait_event_interruptible(device->write_queue,
                !kfifo_is_full(&device->mydemo_fifo));
		if (ret)
			return ret;
	}

	ret = kfifo_from_user(&device->mydemo_fifo, buf, count, &actual_write);
	if (ret)
		return -EIO;

    if (!kfifo_is_empty(&device->mydemo_fifo))
        wake_up_interruptible(&device->read_queue);

	printk("%s:%s pid=%d, actual_write =%d, f_pos=%lld, ret=%d\n", __func__,
			device->name, current->pid, actual_write, *f_pos, ret);

    return actual_write;
}

static unsigned int buffer_char_poll(struct file *file, poll_table *wait)
{
    int mask = 0;
    struct mydemo_private_data *data = file->private_data;
    struct mydemo_device_t *device = data->device;

    poll_wait(file, &device->read_queue, wait);
    poll_wait(file, &device->write_queue, wait);

	if (!kfifo_is_empty(&device->mydemo_fifo))
        mask |= POLLIN | POLLRDNORM;
	if (!kfifo_is_full(&device->mydemo_fifo))
        mask |= POLLOUT | POLLWRNORM;

    return mask;
}

static const struct file_operations buffer_char_fops = {
    .owner = THIS_MODULE,
    .open = buffer_char_open,
    .release = buffer_char_release,
    .read = buffer_char_read,
    .write = buffer_char_write,
    .poll = buffer_char_poll,
};

static int __init buffer_char_init(void)
{
	int ret;
	int i;
	struct mydemo_device_t *device;

	ret = alloc_chrdev_region(&dev, 0, MYDEMO_MAX_DEVICES, DEMO_NAME);
	if (ret) {
		printk("failed to allocate char device region");
		return ret;
	}

	demo_cdev = cdev_alloc();
	if (!demo_cdev) {
		printk("cdev_alloc failed\n");
		goto unregister_chrdev;
	}

	cdev_init(demo_cdev, &buffer_char_fops);
	
	ret = cdev_add(demo_cdev, dev, MYDEMO_MAX_DEVICES);
	if (ret) {
		printk("cdev_add failed\n");
		goto cdev_fail;
	}

	for (i = 0; i < MYDEMO_MAX_DEVICES; i++) {
		device = kmalloc(sizeof(struct mydemo_device_t), GFP_KERNEL);
		if (!device) {
			ret = -ENOMEM;
			goto free_device;
		}

		sprintf(device->name, "%s%d", DEMO_NAME, i);
		mydemo_device[i] = device;
		init_waitqueue_head(&device->read_queue);
		init_waitqueue_head(&device->write_queue);

		ret = kfifo_alloc(&device->mydemo_fifo,
				MYDEMO_FIFO_SIZE,
				GFP_KERNEL);
		if (ret) {
			ret = -ENOMEM;
			goto free_kfifo;
		}

		printk("mydemo_fifo=%p\n", &device->mydemo_fifo);

	}

	printk("succeeded register char device: %s\n", DEMO_NAME);

	return 0;

free_kfifo:
	for (i =0; i < MYDEMO_MAX_DEVICES; i++)
		if (&device->mydemo_fifo)
			 kfifo_free(&device->mydemo_fifo);
free_device:
	for (i =0; i < MYDEMO_MAX_DEVICES; i++)
		if (mydemo_device[i])
			kfree(mydemo_device[i]);
cdev_fail:
	cdev_del(demo_cdev);
unregister_chrdev:
	unregister_chrdev_region(dev, MYDEMO_MAX_DEVICES);
	return ret;
}

static void __exit buffer_char_exit(void)
{
	int i;
	printk("removing device\n");

	if (demo_cdev)
		cdev_del(demo_cdev);

	unregister_chrdev_region(dev, MYDEMO_MAX_DEVICES);

	for (i =0; i < MYDEMO_MAX_DEVICES; i++)
		if (mydemo_device[i])
			kfree(mydemo_device[i]);	
}

module_init(buffer_char_init);
module_exit(buffer_char_exit);

MODULE_AUTHOR("Lin");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("buffer char device");
