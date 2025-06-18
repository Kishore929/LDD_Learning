obj-m       := slpy-proc-ctrl.o

EXTRA_CFLAGS += -DDEBUG

KDIR        := /lib/modules/$(shell uname -r)/build
PWD         := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
