
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kfifo.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

/*************************************************************************/

/*******************global veriable declaration**********************/

unsigned char *pbuffer;
int rd_offset = 0;
int wr_offset = 0;
int buflen = 0;
int ndevices = 1;

dev_t pdevid;

struct cdev cdev;
struct device *pdev;  // global
struct class *pclass; // flobal
struct kfifo myfifo;

////////////////////////////////////////////////////////////////////////////////

/******************************MACROS DEFINITION******************************/

#define MAX_SIZE 1024

#define IOC_MAGIC 'p'
#define MY_IOCTL_LEN _IO(IOC_MAGIC, 1)
#define MY_IOCTL_AVAIL _IO(IOC_MAGIC, 2)
#define MY_IOCTL_RESET _IO(IOC_MAGIC, 3)

/**********Function prototypw declarion*********************/

int pseudo_open(struct inode *inode, struct file *file) {
  printk("Pseudo--open menthod\n");
  return 0;
}

int pseudo_close(struct inode *inode, struct file *file) {
  printk("Pseudo--release method\n");
  return 0;
}

ssize_t pseudo_read(struct file *file, char __user *ubuf, size_t size,
                    loff_t *off) {
  unsigned int rcount, ret;
  char *tbuf;

  if (kfifo_is_full(&myfifo)) {
    printk("buffer is empty\n");
    return 0;
  }
  rcount = size;
  if (rcount > kfifo_len(&myfifo)) {
    rcount = kfifo_len(&myfifo); // min
  }
  tbuf = kmalloc(rcount, GFP_KERNEL);
  kfifo_out(&myfifo, tbuf, rcount);
  ret = copy_to_user(ubuf, tbuf, rcount);
  kfree(tbuf);
  return rcount;
}

ssize_t pseudo_write(struct file *file, const char __user *ubuf, size_t size,
                     loff_t *off) {
  unsigned int wcount, ret;
  char *tbuf;

  if (kfifo_is_full(&myfifo)) {
    printk("buffer is full\n");
    return -ENOSPC;
  }
  wcount = size;
  if (wcount > kfifo_avail(&myfifo)) {
    wcount = kfifo_avail(&myfifo); // min
  }
  tbuf = kmalloc(wcount, GFP_KERNEL);
  ret = copy_from_user(tbuf, ubuf, wcount);
  kfifo_in(&myfifo, tbuf, wcount);
  kfree(tbuf);
  return wcount;
}

/************************IOCTL*********************************************/

static long pseudo_ioctl(struct file *file, unsigned int cmd,
                         unsigned long arg) {

 
  printk("Pseudo--ioctl method\n");
  switch (cmd) {
  case MY_IOCTL_LEN:
    printk("iocltl--kfifo length is %d\n", kfifo_len(&myfifo));
    break;
  case MY_IOCTL_AVAIL:
    printk("ioctl--kfifo avail is %d\n", kfifo_avail(&myfifo));
    break;
  case MY_IOCTL_RESET:
    printk("ioctl--kfifo got reset\n");
    kfifo_reset(&myfifo);
    break;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////

struct file_operations fops = {.open = pseudo_open,
                               .release = pseudo_close,
                               .write = pseudo_write,
                               .read = pseudo_read,
                               .unlocked_ioctl = pseudo_ioctl};

/******* init**************/

static int __init psuedo_init(void) {
  int ret1, ret2;
  int i = 0;

  pclass = class_create(THIS_MODULE, "pseudo_class");

  ret1 = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
  pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
  kfifo_init(&myfifo, pbuffer, MAX_SIZE);
  cdev_init(&cdev, &fops);
  kobject_set_name(&cdev.kobj, "pdevice%d", i);
  ret2 = cdev_add(&cdev, pdevid, 1);
  pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d", i);
  printk("cdev_add ret2 %d", ret2);

  if (ret1) {
    printk("Pseudo: Failed to register driver \n");
    return -EINVAL;
  }
  printk("Successfully registered, major=%d, minor=%d\n", MAJOR(pdevid),
         MINOR(pdevid));
  printk("Pseudo Driver Sample...welcome\n");

  if (ret2) {
    printk("character device added");
  }
  if (pdev) {
    printk("device created");
  }
  return 0;
}

/**************************************  In exit  ****************************/

static void __exit psuedo_exit(void) {

  device_destroy(pclass, pdevid);
  cdev_del(&cdev);
  // kfifo_free(pbuffer);
  unregister_chrdev_region(pdevid, ndevices);
  class_destroy(pclass);
  printk("Pseudo Driver Sample...Bye\n");
}
/////////////////////////////////////////////////////////////////////////////////

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHISHEK MISHRA");
MODULE_DESCRIPTION("Parameter demo Module");
