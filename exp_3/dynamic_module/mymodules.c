#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int mymodule_init(void) {
  printk(KERN_INFO "hello,my module world! \n");
  return 0;
}
static void mymodule_exit(void) {
  printk(KERN_INFO "goodbye,unloading my module.\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
