/*
 * File name: hello_world.c
 */
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

#define SCULL_MAJOR 0
#define SCULL_MINOR 0
#define SCULL_NR_DEVS 4

int scull_major = SCULL_MAJOR;
int scull_minor = SCULL_MINOR;
int scull_nr_devs = SCULL_NR_DEVS;	/* number of bare scull devices */

static int scull_init(void)
{
    int ret;
    dev_t dev = 0;

    dev = MKDEV(scull_major, scull_minor);
    ret = register_chrdev_region(dev, scull_nr_devs, "scull");


	printk(KERN_ALERT "Hello, world\n");
	return 0;
}

static void scull_exit(void)
{
	printk(KERN_EMERG "Goodbye, cruel world\n");
}

module_init(scull_init);
module_exit(scull_exit);
