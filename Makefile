#Makefile Script for kernel modules preperation
#Put all files in one folder called tmpmod and delete it at end

INSTALLDIR = tmpmod

#check the KERNELRELEASE variable to be empty it will not be empty if its second pass after 
#invoking kernel's Makefile
#----------------------------------------------------------------
ifneq (${KERNELRELEASE},)
	obj-m := dummy.o

	dummy-objs := module.o
#----------------------------------------------------------------
else
# KERNELRELEASE is not empty do this 
#----------------------------------------------------------------
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@rm -rf ${INSTALLDIR}
	@mkdir ${INSTALLDIR}
	@mv -f *.o *.ko *.mod.c .*.cmd ${INSTALLDIR}
clean:
	@rm -rf ${INSTALLDIR}
	@rm *.order
	@rm *.symvers
#----------------------------------------------------------------

endif


