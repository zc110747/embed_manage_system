KERNELDIR := /home/user/Develop/Trunk/Sdks/linux-sdk/
CURRENT_PATH := $(shell pwd)
obj-m := kernal_i2c_ap.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
	rm *.order
	rm *.symvers
	rm *.o*
	rm .*.*.cmd
	rm *.mod.c
	mv *.ko ../DriverFIles/
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
