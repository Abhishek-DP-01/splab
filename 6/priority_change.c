#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>


static int pid_to_change = -1; // The PID of the process to change
static int new_priority = 100; // The new priority value (adjust as needed)

module_param(pid_to_change, int, S_IRUGO); // Accept PID as a module parameter
module_param(new_priority, int, S_IRUGO);  // Accept new priority as a module parameter

static int __init task_details_lkm_init(void) {
     struct task_struct *task;
     
     if (pid_to_change <= 0 || new_priority < -20 || new_priority > 19) {
        printk(KERN_ERR "Invalid parameters\n");
        return -EINVAL;
    }

    printk(KERN_INFO "Initializing LKM for CPU scheduling...\n");
    for_each_process(task) {
       if (task->pid == pid_to_change) {
            // Change the priority of the specified process
            set_user_nice(task, new_priority);
            printk(KERN_INFO "Changed priority of PID %d to %d\n", pid_to_change, new_priority);
            break;
        }
     }

    printk(KERN_INFO "LKM initialized\n");

    return 0;
}

static void __exit task_details_lkm_exit(void) {
        printk(KERN_INFO "Exiting LKM...\n");
    printk(KERN_INFO "LKM exited\n");
}

module_init(task_details_lkm_init);
module_exit(task_details_lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM for printing task details in a proc file");

