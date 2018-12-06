/*************************************************************************
	> File Name: hello-4.c
	> Author: Kaixin
	> Mail: 
	> Created Time: Wed 05 Dec 2018 08:00:01 AM PST
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#define DRIVER_AUTHOR "kaixin"
#define DRIVER_DESC "a sample driver"


static int hello_4_data __initdata = 4; 

static int __init hello_4_init(void) {
    printk(KERN_INFO "Hello world %d.!\n", hello_4_data);
    return 0;
}

static void __exit hello_4_exit(void) {
    printk(KERN_INFO "Good bye 4.!\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");
