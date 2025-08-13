#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct process_info {
    pid_t pid;
    char comm[TASK_COMM_LEN];
};

static struct process_info *procs;
static int count = 0;

static int __init proc_init(void)
{
    struct task_struct *task;
    int i = 0;

    for_each_process(task) count++; // Count processes
    procs = kmalloc_array(count, sizeof(*procs), GFP_KERNEL);
    if (!procs) return -ENOMEM;

    for_each_process(task) { // Store info
        procs[i].pid = task->pid;
        strncpy(procs[i].comm, task->comm, TASK_COMM_LEN);
        pr_info("PID: %d | Name: %s\n", procs[i].pid, procs[i].comm);
        i++;
    }
    return 0;
}

static void __exit proc_exit(void)
{
    kfree(procs);
    pr_info("Freed process info memory\n");
}

module_init(proc_init);
module_exit(proc_exit);
