/*
 * File name: simple_mod.c
 */

#include "linux/module.h"
#include "linux/fs.h"
#include "linux/uaccess.h"
#include "linux/init.h"
#include "linux/cdev.h"

#include "linux/miscdevice.h"

#define DEMO_NAME "misc_char_dev"

static struct device *misc_dev;

static int misc_char_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);

    printk("%s : major=%d, minor=%d\n", __func__, major, minor);

    return 0;
}

static int misc_char_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t
misc_char_read(struct file *file, char __user *buf, size_t count,
        loff_t *f_pos)
{
    printk("%s enter\n", __func__);

    return 0;
}

static ssize_t
misc_char_write(struct file *file, const char __user *buf, size_t count,
        loff_t *f_pos)
{
    printk("%s enter\n", __func__);

    return 0;
}

static const struct file_operations misc_char_fops = {
    .owner = THIS_MODULE,
    .open = misc_char_open,
    .release = misc_char_release,
    .read = misc_char_read,
    .write = misc_char_write,
};

static struct miscdevice misc_char_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEMO_NAME,
    .fops = &misc_char_fops,
};

static int __init misc_char_init(void)
{
    int ret;

    ret = misc_register(&misc_char_device);
    if (ret) {
        printk("failed to register misc device\n");
        return ret;
    }

    misc_dev = misc_char_device.this_device;

    printk("successed to register misc char device: %s\n", DEMO_NAME);

    return 0;
}

static void __exit misc_char_exit(void)
{
    printk("removing device\n");

    misc_deregister(&misc_char_device);
}

module_init(misc_char_init);
module_exit(misc_char_exit);

MODULE_AUTHOR("Lin");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("misc char device");
