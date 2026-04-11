obj-m += mychar.o

ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-

KBUILD_CFLAGS += -g

all:
	make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C /home/km/KM_GITHUB/beagleboneblack-kernel M=`pwd` modules
 
clean:
	make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C /home/km/KM_GITHUB/beagleboneblack-kernel M=`pwd` clean
