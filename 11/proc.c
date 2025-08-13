// proc_processes.c - Create a /proc file listing PIDs and names

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>        // For proc fs
#include <linux/seq_file.h>       // For sequence file interface
#include <linux/sched/signal.h>   // For task_struct and for_each_process

#define PROC_NAME "my_proc_list"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM that creates /proc file listing PIDs and process names");
MODULE_VERSION("1.0");

// This function runs when /proc/my_proc_list is read
static int show_proc_info(struct seq_file *m, void *v) {
    struct task_struct *task;

    seq_printf(m, "PID\tProcess Name\n");
    seq_printf(m, "-----------------------\n");

    for_each_process(task) {
        seq_printf(m, "%d\t%s\n", task->pid, task->comm);
    }

    return 0;
}

static int open_proc(struct inode *inode, struct file *file) {
    return single_open(file, show_proc_info, NULL);
}

// File operations for /proc entry
static const struct proc_ops proc_file_ops = {
    .proc_open    = open_proc,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

// Module init
static int __init proc_module_init(void) {
    proc_create(PROC_NAME, 0, NULL, &proc_file_ops);
    printk(KERN_INFO "/proc/%s created.\n", PROC_NAME);
    return 0;
}

// Module exit
static void __exit proc_module_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed.\n", PROC_NAME);
}

module_init(proc_module_init);
module_exit(proc_module_exit);
