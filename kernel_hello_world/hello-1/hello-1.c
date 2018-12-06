/*************************************************************************
	> File Name: hello-1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 08:00:01 AM PST
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void) {
    printk(KERN_INFO "Hello world 1.!\n");
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Good bye 1.!\n");
}
