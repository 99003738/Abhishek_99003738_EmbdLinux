#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched.h>

#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE0(my_sysCall_test2) {

    struct task_struct *task;
    for_each_process(task)
        pr_info("%s [%d]\n", task->comm, task->pid);

    return 0;
}


