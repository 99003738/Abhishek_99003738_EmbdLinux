
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h> // for threads
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/semaphore.h>

static struct task_struct *task1;
static struct task_struct *task2;
static struct task_struct *task3;
static struct task_struct *task4;

static int val = 100;
int max = 10;
static int nval = 100;

module_param(max,int,S_IRUGO);


static int thread_one(void *pargs) {
  int i;
 
  for (i = 1; i <= max; i++) {
    val++;
    //printk("A\n");
    msleep(2);
  }
  
  printk("value of val in A %d \n",val);
  do_exit(0);
  return 0;
  
}

static int thread_two(void *pargs) {
  int i;
  
  for (i =1; i <=max; i++) {
    val--;
    //printk("B\n");
    msleep(2);
  }
  printk("value of val in B %d \n",val);
  do_exit(0);
  return 0;
}

static int thread_three(void *pargs) {
  int i;
  
  for (i =1; i <=max; i++) {
    nval++;
    printk("C\n");
    msleep(2);
  }
  printk("value of nval is %d \n",nval);
  do_exit(0);
  return 0;
}

static int thread_four(void *pargs) {
  int i;
  
  for (i =1; i <=max; i++) {
    nval--;
    printk("D\n");
    msleep(2);
  }
  printk("value of nval is %d \n",nval);
  do_exit(0);
  return 0;
}



// tdemo_init:

static int __init knlthread_init(void) {
  printk("Thread demo ... Welcome");
  task1 = kthread_run(thread_one, NULL, "thread_A");
  printk("Thread A ... Welcome");
  task3 = kthread_run(thread_three, NULL, "thread_C");
  printk("Thread B ... Welcome");
  task2 = kthread_run(thread_two, NULL, "thread_B");
  task4 = kthread_run(thread_four, NULL, "thread_D");
  return 0;
}

static void __exit knlthread_exit(void) {
  printk("final value of val after task 2 %d", val);
  /*if (task1){
    kthread_stop(task1);
    printk("final value of val after task 1 %d", val);
    }
  if (task2){
    kthread_stop(task2);*/
    
    
}

module_init(knlthread_init);
module_exit(knlthread_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHISHEK MISHRA");
MODULE_DESCRIPTION("Parameter demo Module");
