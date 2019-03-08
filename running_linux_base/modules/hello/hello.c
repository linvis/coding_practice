/*
 * File name: hello.c
 */
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk("hello world init\n");

    return 0;
}

static void __exit hello_exit(void)
{
    printk("goodbye\n");
}

module_init(hello_init);
module_exit(hello_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lin");
MODULE_DESCRIPTION("my hello world module");
