/* 
   ECE 373
   Josh Pradera
   Hello Kernel
*/


#include <linux/init.h>    
#include <linux/module.h>  

// Module License. 
MODULE_LICENSE("GPL");

// Kernel init
static int __init hello_init(void){
  printk(KERN_INFO "Hello, Kernel.\n");
  return(0);
} 

static void __exit hello_exit(void){
  printk(KERN_INFO "Goodbye, Kernel.\n");
  return(0);
} 

// Executing Module 
module_init(hello_init);

// Exiting module
module_exit(hello_exit);
