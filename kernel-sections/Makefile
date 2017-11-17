PWD = $(shell pwd)

MOD = kernel-sections.ko
obj-m += kernel-sections.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo insmod kernel-sections.ko

uninstall:
	sudo rmmod kernel-sections.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	rm -rf *.o
	rm -rf *.ko
	rm -rf *.mod.c
	rm -rf modules.order
	rm -rf Module.symvers

reload:
	sudo rmmod $(MOD)
	sudo insmod $(MOD)
