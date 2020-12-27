#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define MAJOR_NUM 290
#define MSG_MAX_LENGTH 140+1
static ssize_t globalvar_read(struct file *, char *, size_t, loff_t*);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);

static char global_var[MSG_MAX_LENGTH] = "EMPTY.";
struct file_operations globalvar_fops = {
    read: globalvar_read,
    write: globalvar_write
};

static int init_mymodule(void) {
    int ret;
    ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops);
    if (ret) { printk("globalvar register failure"); }
    else { printk("globalvar register success"); }

    return ret;
}

static void cleanup_mymodule(void) {
    printk("globalvar unregister success");
    unregister_chrdev(MAJOR_NUM, "globalvar");
}

static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off) {
    if(copy_to_user(buf, &global_var, sizeof(global_var))){ return -EFAULT; }
    return sizeof(global_var);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len, loff_t *off) {
    if (copy_from_user(&global_var, buf, sizeof(global_var))) { return -EFAULT; }
    return sizeof(global_var);
}

module_init(init_mymodule);
module_exit(cleanup_mymodule);
MODULE_LICENSE("GPL");