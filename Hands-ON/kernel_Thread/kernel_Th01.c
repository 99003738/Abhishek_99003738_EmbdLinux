
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h> // for threads
#include <linux/module.h>
#include <linux/time.h> // for using jiffie
#include <linux/delay.h>

static struct task_struct *task1;
static struct task_struct *task2;

static int thread_one(void *pargs) {
  int k=0;
  while (!kthread_should_stop()) {
    printk("Thread A-- %d\n", k++);
    msleep(1000);
  }
  do_exit(0);
  return 0;
}

static int thread_two(void *pargs) {
  int k=0;
  while (!kthread_should_stop()) {
    printk("Thread B-- %d\n", k++);
    msleep(1000);
  }
  do_exit(0);
  return 0;
}

// tdemo_init:

static int __init knlthread_init(void) {
  task1 = kthread_run(thread_one, NULL, "thread_A");
  task2 = kthread_run(thread_two, NULL, "thread_B");
  return 0;
}

static void __exit knlthread_exit(void) {

  if (task1)
    kthread_stop(task1);
  if (task2)
    kthread_stop(task2);
}

module_init(knlthread_init);
module_exit(knlthread_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHISHEK MISHRA");
MODULE_DESCRIPTION("Parameter demo Module");
