obj-m += inat.o

inat-y := kernel/core/persist.o kernel/src/main.o

ccflags-y := -I$(src)/kernel/include

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all clean

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean