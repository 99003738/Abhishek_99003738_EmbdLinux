
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int ndevices=5;

module_param(ndevices,int,S_IRUGO);


static int __init pdemo_init(void)
{

printk("Hello World..welcome\n");
return 0;

}

static void __exit pdemo_exit(void)
{

printk("Bye, Leaving the world\n");

}

module_init(pdemo_init);
module_exit(pdemo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(" ABHISHEK MISHRA");
MODULE_DESCRIPTION(" A Simple Module");
