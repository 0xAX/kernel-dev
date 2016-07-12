PWD = $(shell pwd)

MOD=dump_kern_symbols.ko
obj-m += dump_kern_symbols.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

reload:
	sudo rmmod $(MOD)
	sudo insmod $(MOD)
