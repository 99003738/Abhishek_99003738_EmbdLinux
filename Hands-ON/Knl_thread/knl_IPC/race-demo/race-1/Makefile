obj-m += thdemo.o

KSRC=/home/bltsl02527/ebuildws/kernel_ws/linux-4.14.199
ARCH=arm
CROSS_COMPILE_PREFIX=arm-linux-gnueabi-

all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} clean  ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

