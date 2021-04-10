#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/semaphore.h>

static struct task_struct *task1;
static struct task_struct *task2;

static DEFINE_SEMAPHORE(s1);

static int val=100;
int maxlen=1;
module_param(maxlen,int,S_IRUGO);

static int thread_one(void *pargs)
{
   int i,a;
   a=down_interruptible(&s1);
   for(i=1;i<=maxlen;i++)
   {
     val++;
     //ssleep, usleep
     printk("Thread A");
   }
   up(&s1);
   do_exit(0);
   return 0;
}

static int thread_two(void *pargs)
{
   int i,a;
   a=down_interruptible(&s1);
   for(i=1;i<=maxlen;i++)
   {
     val--; //ssleep, usleep
     printk("Thread B");
   }
   up(&s1);
   do_exit(0);
   return 0;
}
static int __init task_init(void) {  
  sema_init(&s1,1);    //init_module
  task1=kthread_run(thread_one, NULL, "thread_A");  //kthread_create + wake_up_process
  task2=kthread_run(thread_two, NULL, "thread_B");
  printk("Thread Demo..welcome\n");
  return 0;
}
static void __exit task_exit(void) {       //cleanup_module
  /*if(task1)
      kthread_stop(task1);
  if(task2)
      kthread_stop(task2);*/
  printk("Thread Demo,Leaving the world,val=%d\n",val);
}


module_init(task_init);
module_exit(task_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHISHEK MISHRA");
MODULE_DESCRIPTION("A Simple Driver");
