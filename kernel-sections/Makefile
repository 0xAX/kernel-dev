PWD = $(shell pwd)

MOD=kernel-sections.ko
obj-m += kernel-sections.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

reload:
	sudo rmmod $(MOD)
	sudo insmod $(MOD)
