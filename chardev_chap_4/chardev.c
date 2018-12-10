/*************************************************************************
	> File Name: chardev.c
	> Author: Kaixin Huang
	> Mail: 
 ************************************************************************/

/**
 *
 * chardev.c: Creates a read-only char device that says how many times
 * you have read from the dev file 
 */

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<asm/uaccess.h>  // for put_user

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN];
static char *msg_Ptr;

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

/*
 * function is called when loaded
 */
int init_module(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        printk(KERN_ALERT "register failed with %d.\n", Major);
        return Major;
    }

    printk(KERN_INFO "assigned major number: %d.\n", Major);
    printk(KERN_INFO "mknod /dev/%s c %d 0", DEVICE_NAME, Major);
    printk(KERN_INFO "try various minor numbers, try to cat and echo to the device file.\n");
    printk(KERN_INFO "remove the device file ad module when done.\n");

    return SUCCESS;
}

/*
 * function is called when unloaded
 */
void cleanup_module(void) {
    unregister_chrdev(Major, DEVICE_NAME);
}


/*
 * Methods
 */

/*
 * called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
static int device_open(struct inode *inode, struct file *file) {
    static int counter = 0;
    if (Device_Open) {
        return -EBUSY;
    }
    Device_Open++;
    sprintf(msg, "%d times Hello World!\n", counter++);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

/*
 * called when a process closes the device file
 */
static int device_release(struct inode *inode, struct file *file) {
    Device_Open--;
    module_put(THIS_MODULE);
    return 0;
}

/*
 * called when a process wants to read from an opened device file 
 * @filp: see include/linux/fs.h
 * @buff: buffer to fill with data
 * @length: length of the buffer
 */
static ssize_t device_read(struct file *filp, char *buff, size_t length, loff_t *offset) {
    int bytes_read = 0;
    if (*msg_Ptr == 0) {
        return 0;
    }
    while (length && *msg_Ptr) {
        /*
         * the buffer is in the user segment, not the kernel 
         * segment so "*" assigned won't work. 
         * we have to use put_user which copies data from the kernel
         * segment to the user segment.
         */
        put_user(*(msg_Ptr++), buff++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t length, loff_t *offset) {
    printk(KERN_ALERT "write denied!\n");
    return -EINVAL;
}
