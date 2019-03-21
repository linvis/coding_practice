/*
 * File name: simple_mod.c
 */

#include "linux/module.h"
#include "linux/fs.h"
#include "linux/uaccess.h"
#include "linux/init.h"
#include "linux/cdev.h"

#define DEMO_NAME "simple_char_dev"

static dev_t char_dev;
static struct cdev *char_cdev;
static signed count = 1;

static int simple_char_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);

    printk("%s : major=%d, minor=%d\n", __func__, major, minor);

    return 0;
}

static int simple_char_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t
simple_char_read(struct file *file, char __user *buf, size_t count,
        loff_t *f_pos)
{
    printk("%s enter\n", __func__);

    return 0;
}

static ssize_t
simple_char_write(struct file *file, const char __user *buf, size_t count,
        loff_t *f_pos)
{
    printk("%s enter\n", __func__);

    return 0;
}

static const struct file_operations simple_char_fops = {
    .owner = THIS_MODULE,
    .open = simple_char_open,
    .release = simple_char_release,
    .read = simple_char_read,
    .write = simple_char_write,
};

static int __init simple_char_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&char_dev, 0, count, DEMO_NAME);
    if (ret) {
        printk("failed to allocate char device region\n");
        return ret;
    }

    char_cdev = cdev_alloc();
    if (!char_cdev) {
        printk("cdev_alloc failed\n");
        goto unregister_chrdev;
    }

    cdev_init(char_cdev, &simple_char_fops);

    ret = cdev_add(char_cdev, char_dev, count);
    if (ret) {
        printk("cdev_add failed\n");
        goto cdev_fail;
    }

    printk("successeed register char device: %s\n", DEMO_NAME);
    printk("Major number = %d, minor number = %d\n", MAJOR(char_dev), MINOR(char_dev));

    return 0;

cdev_fail:
    cdev_del(char_cdev);

unregister_chrdev:
    unregister_chrdev_region(char_dev, count);

    return ret;
}

static void __exit simple_char_exit(void)
{
    printk("removing device\n");

    if (char_cdev)
        cdev_del(char_cdev);

    unregister_chrdev_region(char_dev, count);
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_AUTHOR("Lin");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("simple char device");
