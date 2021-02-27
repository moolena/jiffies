#include<linux/init.h>
#include<linux/module.h>
#include <linux/uaccess.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/device.h>
#include<linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

struct proc_dir_entry *my_proc;

unsigned long start_time, end_time;

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t * pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

int proc_init(void) {
    /* store kernel started time */
    start_time = jiffies/HZ; 
    my_proc = proc_create(PROC_NAME, 0666, NULL, &proc_ops); 
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    printk(KERN_INFO "Kernal Module started at time %lu\n", start_time);
    return 0;
}

/* exit routing of kernel module*/
void proc_exit(void) {
    remove_proc_entry(PROC_NAME,NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
    printk(KERN_INFO "Kernel Module ended at time %lu\n", end_time);
    return;
}

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos) {
    static int completed = 0;

    if(completed) {
    completed = 0;
    return 0;
}

completed = 1;

end_time = jiffies/HZ; /* stored end time */

sprintf(buf, "Total time Kernel Module ran is %lu seconds \n", end_time - start_time );
return strlen(buf);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("SGG");