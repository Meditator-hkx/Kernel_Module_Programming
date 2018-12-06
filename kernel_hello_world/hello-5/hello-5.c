/*************************************************************************
	> File Name: hello-5.c
	> Author: Kaixin
	> Mail: 
	> Created Time: Wed 05 Dec 2018 08:00:01 AM PST
 ************************************************************************/
/*
 * Passing command line arguments to a module
 */


#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/stat.h>

static short int myshort = 5;
static int myint = 12345;
static long int mylong = 12345678;
static char *mystr = "this is the fifth test";
static int myIntArray[2] = { -1, 1 };
static int arr_argc = 0;

/*
 * module_param(foo, int, 0000)
 * first param: param name;
 * second param: data type;
 * third param: permission bits.
 */
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "a short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "an integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "a long integer");
module_param(mystr, charp, 0000);
MODULE_PARM_DESC(mystr, "a character string");
/*
 * module_param(name, type, num, perm)
 * first param: param name;
 * second param: data type;
 * third param: a pointer to the variable that will store the number;
 * fourth param: permission bits.
 */
module_param_array(myIntArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myIntArray, "an array of integers");

static int hello_5_data __initdata = 5; 

static int __init hello_5_init(void) {
    int i;
    printk(KERN_INFO "Hello world %d.!\n", hello_5_data);
    printk(KERN_INFO "myshort is: %hd\n", myshort);
    printk(KERN_INFO "myint is: %d\n", myint);
    printk(KERN_INFO "mylong is: %ld\n", mylong);
    printk(KERN_INFO "mystr is: %s\n", mystr);
    for (i = 0;i < sizeof(myIntArray) / sizeof(int);i++) {
        printk(KERN_INFO "myIntArray[%d] = %d\n", i, myIntArray[i]);
    }
    printk(KERN_INFO "got %d arguments for myIntArray\n", arr_argc);
    return 0;
}

static void __exit hello_5_exit(void) {
    printk(KERN_INFO "Good bye 5.!\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("kaixin");
MODULE_DESCRIPTION("a sample device");
MODULE_SUPPORTED_DEVICE("testdevice");
