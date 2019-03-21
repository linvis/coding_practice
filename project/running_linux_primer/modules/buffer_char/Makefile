BASEINCLUDE ?= /home/parallels/wspace/linux/runninglinuxkernel_4.0-nogitlog
# BASEINCLUDE ?= /lib/modules/`uname -r`/build

bufferchar-objs := buffer_char.o
obj-m := bufferchar.o

all :
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko
