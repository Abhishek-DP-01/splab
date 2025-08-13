#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h> 

static int irq=10;
module_param(irq,int,0660);

static int debug=0;
module_param(debug,int,0660);

static char *devname = "simpdev";
module_param(devname,charp,0660);

static int addr[10];
static int count;
module_param_array(addr, int, &count,  0660);

static int simple_init(void)
{
	int i;
	printk(KERN_WARNING "hello... irq=%d name=%s debug=%d\n",irq,devname,debug);
	for(i=0;i<count;i++)
		printk(KERN_WARNING "hello... addr=%d \n",addr[i]);
	return 0;
}

static void simple_cleanup(void)
{
	printk(KERN_WARNING "bye... irq=%d name=%s debug=%d\n",irq,devname,debug);
}

MODULE_LICENSE("GPL");
module_init(simple_init);
module_exit(simple_cleanup);

