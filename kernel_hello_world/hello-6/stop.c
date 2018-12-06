/*************************************************************************
	> File Name: stop.c
	> Author: Kaixin Huang
	> Mail: 
 ************************************************************************/


#include<linux/module.h>
#include<linux/kernel.h>

void cleanup_module() {
    printk(KERN_INFO "Good bye 6.");
} 
