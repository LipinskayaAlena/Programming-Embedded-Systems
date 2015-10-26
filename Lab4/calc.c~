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
static long result;

static ssize_t functionRead(struct file *file, char *buf, size_t count, loff_t *ppos);
static ssize_t functionWrite(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
static int functionInit(void);
static void functionExit(void);
static int calculate(void);

struct file_operations my_fops = {
	.owner   = THIS_MODULE,
	.read    = functionRead,
	.write   = functionWrite,
};

static int calculate(void)
{
	switch (operation)
	{
		case '+': 
			result = first + second;
			break;
		case '-':
			result = first - second;
			break;
		case '*':
			result = first * second;
			break;
		case '/':
			if(second == 0)
				return 1;
			else result = first / second;
			break;
		default:
			return -1;
	}
	return 0;
}
static ssize_t functionRead(struct file *file, char *buf, size_t len, loff_t *ppos) 
{ 
	int calculating = 0;
	char message[256];

	calculating = calculate();
	switch (MINOR(file_inode(file)->i_rdev)) {
		case 3:
			if(calculating == 0)
				snprintf(message, sizeof(message), "Result: %ld \n", result);
			else if(calculating == 1)
				snprintf(message, sizeof(message), "ERROR! DIVISION ON ZERO!\n");
			else if(calculating == -1)
				snprintf(message, sizeof(message), "ERROR! WRONG OPERATION!\n");
			break;		
	}

	
	size_of_message = strlen(message);
   
	if (message[*ppos] == '\0')
		return 0;

	copy_to_user(buf, &message[*ppos], 1);
	*ppos += 1;
	return 1;
} 

static ssize_t functionWrite(struct file *file,	const char __user * buf, size_t length, loff_t * offset) 
{
   char buffer[256];
   
   copy_from_user(buffer, buf, sizeof(buf));

   switch (MINOR(file_inode(file)->i_rdev)) {
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

static int functionInit(void)
{
	int regist = 0;
    
	regist = register_chrdev(200, "calc", &my_fops); 
	if (regist < 0) { 
		printk(KERN_ERR "Can not register char device\n"); 
		return regist;
	}
	return 0;
}
 

static void functionExit(void)
{
 	unregister_chrdev(200, "calc");
	printk(KERN_ALERT "Device unregistered\n");
}

module_init(functionInit);
module_exit(functionExit);
