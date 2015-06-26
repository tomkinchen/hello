#Makefile for hello.cfile
#
KERNEL_DIR:=/usr/src/linux-headers-$(shell uname -r)

obj-m:=hello.o

default:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	$(RM) .*.cmd *.mod.c *.o *.ko *.order *.symvers -r .tmp*
