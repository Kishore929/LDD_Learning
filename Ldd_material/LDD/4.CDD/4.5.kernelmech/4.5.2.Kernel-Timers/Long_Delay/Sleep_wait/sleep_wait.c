/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *                                                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>


static struct task_struct *sender_thread = NULL;

static int my_sender_thread (void *data)
{

    do {
        printk (KERN_INFO "my_sender_thread sent a message at jiffies=%ld\n",
                jiffies);
        set_current_state(TASK_INTERRUPTIBLE);
        schedule_timeout(msecs_to_jiffies(10000));//10 sec delay
   } while (!kthread_should_stop ());

    return 0;

}                               

static int __init my_init (void)
{

    sender_thread = kthread_run (my_sender_thread, NULL, "sender_thread");
    if (IS_ERR (sender_thread)) {
        printk (KERN_INFO "Error %ld creating thread\n",
                PTR_ERR (sender_thread));
        return -1;
    }

    printk ("Starting Kernel thread in init module\n");

    return 0;
}

static void __exit my_exit (void)
{
    printk (KERN_INFO "exiting module, stopping Kernel thread\n");
    kthread_stop (sender_thread);
}

module_exit (my_exit);
module_init (my_init);

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Simple demo of a kernel timer: Sleepwait approach");
MODULE_LICENSE("GPL v2");
