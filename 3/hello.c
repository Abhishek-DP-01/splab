#include <linux/init.h>      // For module_init and module_exit macros
#include <linux/module.h>    // For all kernel modules
#include <linux/kernel.h>    // For KERN_INFO

// Metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Hello World LKM");

// Function called when module is loaded
static int __init hello_init(void) {
    printk(KERN_INFO "Hello! Kernel module loaded.\n");
    return 0; // 0 = success
}

// Function called when module is removed
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye! Kernel module unloaded.\n");
}

// Register init and exit functions
module_init(hello_init);
module_exit(hello_exit);
