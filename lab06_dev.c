#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timer;

static long timeout = 2000;

void time_handler(unsigned long data);

static ssize_t write_handler(struct file *filp, const char *buff, size_t count, loff_t *offp);

static const struct file_operations fops;

static struct miscdevice lab06_dev;

static int __init lab_init(void);

module_init(lab_init);

static void __exit lab_exit(void);

module_exit(lab_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Poltorackiy Alex");
MODULE_DESCRIPTION("\"Lab06\" module");
MODULE_VERSION("dev");
