#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kfifo.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>


#define MAX_SIZE 1024

static int buflen=0; 
static int check =0;                           //wait_event_interruptible(w1, (buflen > 0) );

struct cdev cdev;
dev_t pdevid;
int ndevices=1;
struct device *pdev; //global
struct class *pclass; //global
struct kfifo kfifo;

unsigned char *pbuffer;



static struct task_struct *task1;
static struct task_struct *task2;
static struct task_struct *task3;

wait_queue_head_t w1;
wait_queue_head_t w2;
DEFINE_MUTEX(m1);

int pseudo_open(struct inode* inode , struct file* file)
{
  printk("Pseudo--open method\n");
  return 0;
}


int pseudo_close(struct inode* inode , struct file* file)
{
  printk("Pseudo--release method\n");
  return 0;
}

ssize_t pseudo_write(struct file * file, const char __user * ubuf , size_t size, loff_t * off)
{
  int wcount,ret;
  char *tbuf;
  if(kfifo_is_full(&kfifo))
  {
     printk("buffer is full\n");
     return -ENOSPC;
   }
   wcount = size;
   if(wcount > kfifo_avail(&kfifo))
   {
     wcount = kfifo_avail(&kfifo);
   }
   tbuf=kmalloc(wcount, GFP_KERNEL);
   ret=copy_from_user(tbuf, ubuf, wcount);
   if(ret)
   {
      printk("copy from user failed\n");
      return -EFAULT;
   }
   kfifo_in(&kfifo, tbuf, wcount);
   kfree(tbuf);
   printk("Pseudo--write method\n");
   return wcount;
}

ssize_t pseudo_read(struct file * file, char __user * ubuf , size_t size, loff_t * off)
{
  int rcount,ret;
  char *tbuf;
  if(kfifo_is_empty(&kfifo)) 
  {
    printk("buffer is empty\n");
    return 0;
   }
   rcount = size;
   if(rcount > kfifo_len(&kfifo))
   {
     rcount = kfifo_len(&kfifo);
   }
   tbuf = kmalloc(rcount, GFP_KERNEL);
   kfifo_out(&kfifo, tbuf, rcount);
   ret=copy_to_user(ubuf, tbuf, rcount);
   if(ret)
   {
     printk("copy to user failed\n");
     return -EFAULT;
   }
   kfree(tbuf);
   printk("Pseudo--read method\n");
   return rcount;
}


struct file_operations fops = {
   .open    = pseudo_open,
   .release = pseudo_close
   //.write   = pseudo_write,
   //.read = pseudo_read 
   };

static int thread_one(void *pargs)
{
    mutex_lock(&m1);
    printk("your ar in %d\n", buflen);
    fops.write = pseudo_write;
    buflen=1;
    printk("you are leaving thread one");
    mutex_unlock(&m1);
    wake_up_interruptible(&w1);
    
    return 0;
}

static int thread_two(void *pargs)
{
    mutex_lock(&m1);
    printk("your ar in %d\n", buflen);
    //wait_event_interruptible(w1, (buflen == 1) );
    printk("thread two");
    fops.write = pseudo_write;
    check=1;
    mutex_unlock(&m1);
    wake_up_interruptible(&w1);
   return 0;
}

static int thread_three(void *pargs)
{
    wait_event_interruptible(w1, (buflen ==1 && check==1 ) );
    printk("you are trying two read");
    fops.read = pseudo_read;
    return 0;
}


static int __init psuedo_init(void)
{
   int ret1,ret2;
   int i=0;
   pclass = class_create(THIS_MODULE, "pseudo_class");
   ret1=alloc_chrdev_region(&pdevid, 0, ndevices, "myfiledriver_sample");
   
   pbuffer=kmalloc(MAX_SIZE, GFP_KERNEL);
   kfifo_init(&kfifo, pbuffer,MAX_SIZE);
   
   if(ret1) 
   {
      printk("Pseudo: Failed to register driver\n");
      return -EINVAL;
   }
   cdev_init(&cdev, &fops);
   kobject_set_name(&cdev.kobj,"pdevice%d", i);
   ret2 = cdev_add(&cdev, pdevid, 1);
   pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d",i);
   
   printk("Successfully registered,major=%d,minor=%d\n",MAJOR(pdevid),   MINOR(pdevid));//MAKEDEV
   printk("Pseudo Driver Sample..welcome\n");
   
   
   init_waitqueue_head(&w1);
   init_waitqueue_head(&w2);
   mutex_init(&m1);
   task1=kthread_run(thread_one, NULL, "thread_write1");
   task2=kthread_run(thread_two, NULL, "thread_write2");
   task3=kthread_run(thread_three, NULL, "thread_read");
   
   
   
   
   return 0;
}


static void __exit psuedo_exit(void)
{
  kfifo_free(&kfifo);
  device_destroy(pclass, pdevid);
  cdev_del(&cdev);
  unregister_chrdev_region(pdevid, ndevices);
  class_destroy(pclass);
  printk("Pseudo Driver Sample..Bye\n");
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shiv");
MODULE_DESCRIPTION("A Simple Driver");

