#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

MODULE_DESCRIPTION("This is a sample module parameter example");
MODULE_AUTHOR("Kernel masters");


int var = 10;
module_param(var,int,0644);

static int modparam_init (void)
{
	printk ("This is modparam init function var:%d\n",var);
	return 0;
}


static void modparam_exit (void)
{
	printk ("This is modparam exit function\n");
}


module_init(modparam_init);
module_exit(modparam_exit);


