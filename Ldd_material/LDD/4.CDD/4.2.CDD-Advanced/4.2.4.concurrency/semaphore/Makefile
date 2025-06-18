obj-m  := one.o
obj-m  += two.o
obj-m  += export.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=`pwd` modules

clean:
	$(MAKE) -C $(KDIR) M=`pwd` clean

