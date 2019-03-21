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

#define MAX_DEVICE_BUFFER_SIZE 64
#define DEMO_NAME "buffer_char"

DEFINE_KFIFO(my_dev_fifo, char, 64);

static struct device *buffer_dev;

static int buffer_char_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);

    printk("%s : major=%d, minor=%d\n", __func__, major, minor);

    return 0;
}

static int buffer_char_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t
buffer_char_read(struct file *file, char __user *buf, size_t count,
        loff_t *f_pos)
{
    int actual_readed;
    int ret;

    ret = kfifo_to_user(&my_dev_fifo, buf, count, &actual_readed);
    if (ret)
        return -EIO;

    printk("%s, actual_readed=%d, pos=%lld, %p\n", __func__, actual_readed, *f_pos, f_pos);

    return actual_readed;
}

static ssize_t
buffer_char_write(struct file *file, const char __user *buf, size_t count,
        loff_t *f_pos)
{
    int actual_write;
    int ret;

    ret = kfifo_from_user(&my_dev_fifo, buf, count, &actual_write);

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

    ret = misc_register(&buffer_char_device);
    if (ret) {
        printk("failed to register buffer device\n");
        return ret;
    }

    buffer_dev = buffer_char_device.this_device;

    printk("successed to register buffer char device: %s\n", DEMO_NAME);

    return 0;
}

static void __exit buffer_char_exit(void)
{
    printk("removing device\n");

    misc_deregister(&buffer_char_device);
}

module_init(buffer_char_init);
module_exit(buffer_char_exit);

MODULE_AUTHOR("Lin");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("buffer char device");
