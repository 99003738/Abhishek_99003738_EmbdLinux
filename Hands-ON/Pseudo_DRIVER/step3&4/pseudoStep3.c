
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

unsigned char *pbuffer;
int rd_offset = 0;
int wr_offset = 0;
int buflen = 0;

dev_t pdevid;
int ndevices = 1;
struct cdev cdev;

struct device *pdev;  // global
struct class *pclass; // flobal

#define MAX_SIZE 500

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
  if (buflen == 0) // wr_offset - rd_offset ==0
  {
    printk("buffer is empty\n");
    return 0;
  }

  rcount = size;
  if (rcount > buflen)
    rcount = buflen; // min of buflen, size
  ret = copy_to_user(ubuf, (pbuffer+rd_offset), rcount);

  if (ret) {
    printk("copy to user failed\n");
    return -EFAULT;
  }

  rd_offset += rcount;
  buflen -= rcount;
  return rcount;
}

ssize_t pseudo_write(struct file *file, const char __user *ubuf, size_t size,
                     loff_t *off) {
  unsigned int wcount, ret;
  //? wcount data pronot declare

  if (wr_offset >= MAX_SIZE) {
    printk("buffer is full\n");
    return -ENOSPC;
  }
  wcount = size;
  if (wcount > (MAX_SIZE - wr_offset)) {
    wcount = (MAX_SIZE - wr_offset);
  }

  ret = copy_from_user((pbuffer+wr_offset), ubuf, wcount);

  if (ret) {
    printk("copy from user failed\n");
    return -EFAULT;
  }

  wr_offset += wcount;
  buflen += wcount;
  return wcount;
}

struct file_operations fops = {.open = pseudo_open,
                               .release = pseudo_close,
                               .write = pseudo_write,
                               .read = pseudo_read
                              };

// init

static int __init psuedo_init(void) {
  int ret1, ret2;
  int i = 0;
  
  pclass = class_create(THIS_MODULE, "pseudo_class");

  ret1 = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample"); 
  pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);   // 
  cdev_init(&cdev, &fops);
  kobject_set_name(&cdev.kobj, "pdevice%d", i);
  ret2 = cdev_add(&cdev, pdevid, 1);
  pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d", i);
  printk("cdev_add ret2 %d",ret2);

  if (ret1) {
    printk("Pseudo: Failed to register driver \n");
    return -EINVAL;
  }
  printk("Successfully registered, major=%d, minor=%d\n", MAJOR(pdevid),
         MINOR(pdevid));
  printk("Pseudo Driver Sample...welcome\n");

  if(ret2){
    printk("character device added");
    }
  if(pdev)
  {
    printk("device created");
  }
}

// In exit

static void __exit psuedo_exit(void) {


  device_destroy(pclass, pdevid);
  cdev_del(&cdev);
  kfree(pbuffer);
  unregister_chrdev_region(pdevid, ndevices);
  class_destroy(pclass);
  printk("Pseudo Driver Sample...Bye\n");
  
 
  
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHISHEK MISHRA");
MODULE_DESCRIPTION("Parameter demo Module");
