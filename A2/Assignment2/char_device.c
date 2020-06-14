/*
  ECE 373
  Josh Pradera 
  Assignment2: Character Device Driver
*/

#include <linux/module.h>  
#include <linux/slab.h>   
#include <linux/types.h>
#include <linux/uaccess.h> 
#include <linux/kdev_t.h>  
#include <linux/cdev.h>
#include <linux/fs.h>         
#include <linux/usb.h>     
 


#define device_count 1
#define DEVICE_NAME "charDevice"

MODULE_AUTHOR("Josh Pradera");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");



// Declaring the char device struct
static struct cdev cdev;
static int sycallV = 25;

// Creating a dev_t
static dev_t mydev_node;

module_param(sycallV, int, S_IRUSR | S_IWUSR);

// Opening function module Open Function
static int charDevice_open(struct inode *inode, struct file *file){
  printk(KERN_INFO "charDevice module has opened.\n");
  return(0);
}

static ssize_t charDevice_read(struct file *file, char __user *buffer, size_t L, loff_t *offset){
  int ret;
  
  // Check if offset is too big
  if (*offset >= sizeof(int)){
    return(0);
  }
  
  if (!buffer){
    ret = -EINVAL;
    goto out;
  }
  
  if (copy_to_user(buffer, &sycallV, sizeof(int))){
    ret = -EFAULT;
    goto out;
  }
 
  ret = sizeof(int);
  *offset += L;
  
  printk(KERN_INFO "User has received %d.\n", sycallV);
  
  out:
    return(ret);
}



// Write function module
static ssize_t charDevice_write(struct file *file, const char __user *buffer, size_t L, loff_t *offset){
  char *kernelBuffer;
  int ret;
  
  if (!buffer){
    ret = -EINVAL;
    goto out;
  }
  
  kernelBuffer = kmalloc(L, GFP_KERNEL);
  
  if (!kernelBuffer){
    ret = -ENOMEM;
    goto out;
  }
 
  if (copy_to_user(kernelBuffer, buffer, L)){
    ret = -EFAULT;
    goto memoryOut;
  }
  ret = L;
  
  printk(KERN_INFO "Userspace = \"%s\" to \n", kernelBuffer);
  

  memoryOut:
    kfree(kernelBuffer);
  out:
    return(ret);
}



// file perations
static struct file_operations mydev_file_ops = {
  .owner = THIS_MODULE,
  .open = charDevice_open,
  .read = charDevice_read,
  .write = charDevice_write,
}; /* File Operations Structure ends. */



//Init function
static int __init cahrDeviceI(void) {

    if (alloc_chrdev_region(&mydev_node, 0, device_count, DEVICE_NAME)) {
        // Indicate fail
        printk(KERN_ERR "allocating chrdev region has failed!\n");
        return(-1);
    }

    // Print the the # of devices allocated in the major number
    printk(KERN_INFO "Allocated %d device in major number %d.\n", device_count, MAJOR(mydev_node));

    // Ok init the char devic 
    cdev_init(&cdev, &mydev_file_ops);
    cdev.owner = THIS_MODULE;

    if (cdev_add(&cdev, mydev_node, device_count)) {
        printk(KERN_ERR " adding the char failed!\n");

        unregister_chrdev_region(mydev_node, device_count);

        return(-1);
    }


    return(0);
}



//Exit module
static void __exit exiting_device(void){
  cdev_del(&cdev);

  unregister_chrdev_region(mydev_node, device_count);
 
  printk(KERN_INFO "The module was removed!.\n");
}

//To initialize and exit module
module_init(cahrDeviceI);
module_exit(exiting_device);
