/*************************************************************************
	> File Name: start.c
	> Author: Kaixin Huang
	> Mail: 
*************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void) {
    printk(KERN_INFO "Hello world 6.");
    return 0;
}
