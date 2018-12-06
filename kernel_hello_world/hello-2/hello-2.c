/*************************************************************************
	> File Name: hello-2.c
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 08:00:01 AM PST
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init hello_2_init(void) {
    printk(KERN_INFO "Hello world 2.!\n");
    return 0;
}

static void __exit hello_2_exit(void) {
    printk(KERN_INFO "Good bye 2.!\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);
