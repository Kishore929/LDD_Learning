#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
 
//Timer Variable
#define TIMEOUT 5000    //milliseconds
static struct timer_list km_timer;
static unsigned int count = 0;
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev km_cdev;
 
static int __init km_driver_init(void);
static void __exit km_driver_exit(void);
static int km_open(struct inode *inode, struct file *file);
static int km_release(struct inode *inode, struct file *file);
static ssize_t km_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t km_write(struct file *filp, const char *buf, size_t len, loff_t * off);
 
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = km_read,
        .write          = km_write,
        .open           = km_open,
        .release        = km_release,
};
 
//Timer Callback function. This will be called when timer expires
void timer_callback(struct timer_list * data)
{
     /* do your timer stuff here */
    printk(KERN_INFO "Timer Callback function Called [%d]\n",count++);
    
    /*
       Re-enable timer. Because this function will be called only first time. 
       If we re-enable this will work like periodic timer. 
    */
    mod_timer(&km_timer, jiffies + msecs_to_jiffies(TIMEOUT));
}
 
static int km_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device File Opened...!!!\n");
    return 0;
}
 
static int km_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device File Closed...!!!\n");
    return 0;
}
 
static ssize_t km_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Read Function\n");
    return 0;
}
static ssize_t km_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Write function\n");
    return 0;
}
 
static int __init km_driver_init(void)
{
    /*Allocating Major number*/
    if((alloc_chrdev_region(&dev, 0, 1, "km_Dev")) <0){
            printk(KERN_INFO "Cannot allocate major number\n");
            return -1;
    }
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
    /*Creating cdev structure*/
    cdev_init(&km_cdev,&fops);
 
    /*Adding character device to the system*/
    if((cdev_add(&km_cdev,dev,1)) < 0){
        printk(KERN_INFO "Cannot add the device to the system\n");
        goto r_class;
    }
 
    /*Creating struct class*/
    if((dev_class = class_create(THIS_MODULE,"km_class")) == NULL){
        printk(KERN_INFO "Cannot create the struct class\n");
        goto r_class;
    }
 
    /*Creating device*/
    if((device_create(dev_class,NULL,dev,NULL,"km_device")) == NULL){
        printk(KERN_INFO "Cannot create the Device 1\n");
        goto r_device;
    }
 
    /* setup your timer to call my_timer_callback */
    timer_setup(&km_timer, timer_callback, 0);       //If you face some issues and using older kernel version, then you can try setup_timer API(Change Callback function's argument to unsingned long instead of struct timer_list *.
 
    /* setup timer interval to based on TIMEOUT Macro */
    mod_timer(&km_timer, jiffies + msecs_to_jiffies(TIMEOUT));
 
    printk(KERN_INFO "Device Driver Insert...Done!!!\n");
    return 0;
r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev,1);
    return -1;
}
 
void __exit km_driver_exit(void)
{
    /* remove kernel timer when unloading module */
    del_timer(&km_timer);
 
    class_destroy(dev_class);
    cdev_del(&km_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}
 
module_init(km_driver_init);
module_exit(km_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple device driver - Kernel Timer");
MODULE_VERSION("1.21");
