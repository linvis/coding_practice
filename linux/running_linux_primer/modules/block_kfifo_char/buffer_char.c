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

#define MAX_DEVICE_BUFFER_SIZE 64
#define DEMO_NAME "buffer_char"

DEFINE_KFIFO(my_dev_fifo, char, 64);

struct mydemo_device_t {
    const char *name;
    struct device *dev;
    struct miscdevice *miscdev;
    wait_queue_head_t read_queue;
    wait_queue_head_t write_queue;
};

struct mydemo_private_data {
    struct mydemo_device_t *device;
};

static struct mydemo_device_t *mydemo_device;

static int buffer_char_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);

    struct mydemo_private_data *data;
    struct mydemo_device_t *device = mydemo_device;

    printk("%s : major=%d, minor=%d\n", __func__, major, minor);

    data = kmalloc(sizeof(struct mydemo_private_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

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

    if (kfifo_is_empty(&my_dev_fifo)) {
        if (file->f_flags & O_NONBLOCK)
            return -EAGAIN;

		printk("%s: pid=%d, going to sleep\n", __func__, current->pid);
        ret = wait_event_interruptible(device->read_queue,
                !kfifo_is_empty(&my_dev_fifo));
        if (ret)
            return ret;

    }

    ret = kfifo_to_user(&my_dev_fifo, buf, count, &actual_readed);
    if (ret)
        return -EIO;

    if (!kfifo_is_full(&my_dev_fifo))
        wake_up_interruptible(&device->write_queue);

    printk("%s, actual_readed=%d, pos=%lld, %p\n", __func__, actual_readed, *f_pos, f_pos);

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

	if (kfifo_is_full(&my_dev_fifo)){
		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;

		printk("%s: pid=%d, going to sleep\n", __func__, current->pid);
        ret = wait_event_interruptible(device->write_queue,
                !kfifo_is_full(&my_dev_fifo));
		if (ret)
			return ret;
	}

    ret = kfifo_from_user(&my_dev_fifo, buf, count, &actual_write);
	if (ret)
		return -EIO;

    if (!kfifo_is_empty(&my_dev_fifo))
        wake_up_interruptible(&device->read_queue);

    printk("%s, actual_write=%d, pos=%lld, %p\n", __func__, actual_write, *f_pos, f_pos);

    return actual_write;
}

static const struct file_operations buffer_char_fops = {
    .owner = THIS_MODULE,
    .open = buffer_char_open,
    .release = buffer_char_release,
    .read = buffer_char_read,
    .write = buffer_char_write,
};

static struct miscdevice buffer_char_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEMO_NAME,
    .fops = &buffer_char_fops,
};

static int __init buffer_char_init(void)
{
    int ret;

    struct mydemo_device_t *device = kmalloc(sizeof(struct mydemo_device_t), GFP_KERNEL);
    if (!device)
        return -ENOMEM;

    ret = misc_register(&buffer_char_device);
    if (ret) {
        printk("failed to register buffer device\n");
        goto free_device;
    }

    device->dev = buffer_char_device.this_device;
    device->miscdev = &buffer_char_device;

    init_waitqueue_head(&device->read_queue);
    init_waitqueue_head(&device->write_queue);

    mydemo_device = device;

    printk("successed to register buffer char device: %s\n", DEMO_NAME);

free_device:
    kfree(device);

    return 0;
}

static void __exit buffer_char_exit(void)
{
    struct mydemo_device_t *dev = mydemo_device;

    printk("removing device\n");

    misc_deregister(dev->miscdev);

    kfree(dev);
}

module_init(buffer_char_init);
module_exit(buffer_char_exit);

MODULE_AUTHOR("Lin");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("buffer char device");
