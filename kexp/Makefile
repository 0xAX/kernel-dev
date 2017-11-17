PWD = $(shell pwd)

MOD = kexp.ko
obj-m += kexp.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc ukexp.c -o ukexp

install:
	sudo insmod kexp.ko

uninstall:
	sudo rmmod kexp.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	rm -rf *.o
	rm -rf *.ko
	rm -rf *.mod.c
	rm -rf modules.order
	rm -rf Module.symvers
	rm -rf ukexp

reload:
	sudo rmmod $(MOD)
	sudo insmod $(MOD)
