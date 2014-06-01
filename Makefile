obj-m := lab06_dev.o 

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
install:
	sudo insmod lab06_dev.ko
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
uninstall:
	sudo rmmod lab06_dev
	sudo rm -rf /dev/lab06
