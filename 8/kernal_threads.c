/*Create an LKM that that will display a list of only those tasks which are ‘kernel threads’? (i.e., task->mm == 0). How many ‘kernel threads’ on your list?*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

int kernel_thread_count = 0, Process_count=0;

static int count_kernel_threads(void) {
    struct task_struct *task;
  
    printk(KERN_INFO "List of Kernel Threads:\n");

    for_each_process(task) {
        if (task->mm == NULL) {  // Kernel threads have task->mm == 0
            printk(KERN_INFO "PID: %d, Name: %s\n", task->pid, task->comm);
            kernel_thread_count++;
        }
        Process_count++;
    }

    return kernel_thread_count;
}

static int __init kernel_threads_init(void) {
    int kernel_thread_count = count_kernel_threads();
    printk(KERN_INFO "Number of Kernel Threads: %d\n", kernel_thread_count);
     printk(KERN_INFO "Number of Kernel Processes: %d\n", Process_count);
    return 0;
}

static void __exit kernel_threads_exit(void) {
    printk(KERN_INFO "Kernel Threads LKM removed\n");
}

module_init(kernel_threads_init);
module_exit(kernel_threads_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM for printing task details in a proc file");

