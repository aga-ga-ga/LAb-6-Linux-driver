#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timer;

static long timeout = 2000;

void time_handler(unsigned long data);

static ssize_t write_handler(struct file *filp, const char *buff, size_t count, loff_t *offp);

//поле owner нужно для организации счетчика ссылок на модуль.
//Счетчик ссылок нужен, чтобы модуль не выгрузили раньше времени, например, если файловая система была примонтирована,
//то выгрузка модуля может привести к краху, счетчик ссылок не позволит выгрузить модуль, пока он используется,
//т. е. пока мы не размонтируем файловую систему.
static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.write = write_handler
};

static struct miscdevice lab06_dev = {
	MISC_DYNAMIC_MINOR, // автоматически выбираемое 
	"lab06",
	&fops
};

static int __init lab_init(void)
{
	int ret;
	//misc_register() регистрирует единичное устройство
	ret = misc_register(&lab06_dev);
	if (ret) {
		printk(KERN_ERR "Unable to register \"Lab06\" device\n");
	}
	//инициализируем таймер
	//функция time_handler вызывается внутри функции setup_timer
	setup_timer(&timer, time_handler, 0);

	ret = mod_timer(&timer, jiffies + msecs_to_jiffies(timeout));
	if (ret) {
		printk(KERN_ERR "Error in mod_timer\n");
	}


	return ret;
}

module_init(lab_init);

static void __exit lab_exit(void)
{
	misc_deregister(&lab06_dev);
	del_timer(&timer);
}

module_exit(lab_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Poltorackiy Alex");
MODULE_DESCRIPTION("\"Lab06\" module");
MODULE_VERSION("dev");
