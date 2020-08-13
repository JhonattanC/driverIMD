ifneq ($(KERNELRELEASE),)
obj-m := char_driver.o
else
KDIR := $(HOME)/IMD/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif