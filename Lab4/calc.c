#include <linux/cdev.h> 
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/device.h> 
#include <asm/uaccess.h> 

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Lipinskaya AV"); 


static int calc_init(void);
static void calc_exit(void);


static int calc_init(void)
{   
	printk(KERN_INFO "Module init\n"); 
	return 0;
}
 

static void calc_exit(void)
{
    printk(KERN_INFO "Device unregistered\n");
}

module_init(calc_init);
module_exit(calc_exit);
