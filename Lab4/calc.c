#include <linux/cdev.h> 
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/device.h> 
#include <asm/uaccess.h> 

MODULE_AUTHOR("Lipinskaya"); 


static int size_of_message;


static long first;
static long second;
static char operation;

static ssize_t dev_read(struct file * file, char * buf, size_t count, loff_t *ppos);
static ssize_t dev_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
static int dev_open(struct inode *inode, struct file *file);
static int dev_release(struct inode *inode, struct file *file);
static int dev_init(void);
static void dev_exit(void);

struct file_operations my_fops = {
	.owner   = THIS_MODULE,
	.read    = dev_read,
	.write   = dev_write,
	.open    = dev_open,
	.release = dev_release,
};


static ssize_t dev_read(struct file * file, char * buf, 
                         size_t len, loff_t *ppos) 
{ 
	int error = 0;
	int major, minor;
	char message[256];
	memset(message, 0, sizeof(message));
	major = MAJOR(file_inode(file)->i_rdev);
	minor = MINOR(file_inode(file)->i_rdev);
	
	switch(minor) {
		case 3:
			snprintf(message, sizeof(message), "%ld %c %ld \n", first, operation, second);
			break;
	}

	
	size_of_message = strlen(message);

	if (message[*ppos] == '\0') {
        printk(KERN_INFO "End of string, returning zero.\n");
        return 0;
    }

	copy_to_user(buf, &message[*ppos], 1);
	*ppos += 1;
	return 1;
} 

static ssize_t dev_write(struct file *file, 
	const char __user * buf, size_t length, loff_t * offset) 
{
   int major, minor;
   char buffer[256];
   memset(buffer, 0, sizeof(buffer));

   major = MAJOR(file_inode(file)->i_rdev);
   minor = MINOR(file_inode(file)->i_rdev);
   
   copy_from_user(buffer, buf, sizeof(buf));
   switch(minor) {
   	case 0:
   		copy_from_user(buffer, buf, sizeof(buf));
   		kstrtol(buffer, 10, &first);
		break;
	case 1:
		copy_from_user(buffer, buf, sizeof(buf));
		kstrtol(buffer, 10, &second);
   		break;
	case 2: 
		copy_from_user(buffer, buf, sizeof(buf));
		operation = buffer[0];
		break;
   }
   size_of_message = strlen(buffer);
   
   return size_of_message;
} 

static int dev_open(struct inode *inode,struct file *filp)
{
    return 0;
}

static int dev_release(struct inode *inode,struct file *filp)
{
    return 0;
}

static int dev_init(void)
{
	int err = 0;
    
	err = register_chrdev(300, "calc", &my_fops); 
	if(err < 0) { 
		printk(KERN_ERR "Can not register char device\n"); 
		return err;
	}
	return 0;
}
 

static void dev_exit(void)
{
 	unregister_chrdev(300, "calc");
	printk(KERN_ALERT "Device unregistered\n");
}

module_init(dev_init);
module_exit(dev_exit);
