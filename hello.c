#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

/***********var**************************/
static unsigned int regaddr, regdata;


struct hello_dev_t{
	struct cdev cdev;
}hello_dev;


struct file_operations hello_fops = {
	.owner	=	THIS_MODULE,
};

/*********function**********************/
static int hello_world_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int len;

	printk(KERN_INFO "hello world read proc\n");

	len = sprintf(page, "%x %x\n", regaddr, regdata);

	printk(KERN_INFO "read addr(%x),  data(%x), len(%x)\n", regaddr, regdata, len);

	return len;
}

static int hello_world_write(struct file *file, const char *buffer, unsigned long count, void *data)
{
	char regbuf[64] = {'\0'};
//	unsigned int regaddr, regdata;
	int ret = 0;

	printk(KERN_INFO "hello world write proc\n");

	if (copy_from_user(regbuf, buffer, count))
		return -EFAULT;

	if (sscanf(regbuf, "%x %x", &regaddr, &regdata) == 2)
	{
		printk(KERN_INFO "write addr(%x),  data(%x), count(%x)\n", regaddr, regdata, count);
		ret = count;
	}
	
	return ret;
}
static int hello_init(void)
{
	struct proc_dir_entry *prEntry;

	printk(KERN_ALERT "Hello, world\n");

	prEntry = create_proc_entry("hello", 0666, NULL);
	
	prEntry->read_proc = hello_world_read;
	prEntry->write_proc = hello_world_write;
	return 0;
}


static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	
	remove_proc_entry("hello", NULL);
}



module_init(hello_init);
module_exit(hello_exit);
