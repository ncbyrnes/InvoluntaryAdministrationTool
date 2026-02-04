.PHONY: all clean kernel-mod

all: kernel-mod

kernel-mod:
	make -C kernel module

clean:
	make -C kernel clean