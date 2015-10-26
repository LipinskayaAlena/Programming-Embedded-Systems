#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static struct kobject *kobj;

static int my_init(void) 
{
	kobj = kobject_create_and_add("hello", NULL);
	if (!kobj)
		return -ENOMEM;
	return 0;
}

static void my_exit(void) 
{
	kobject_put(kobj);
}

module_init(my_init);
module_exit(my_exit);


