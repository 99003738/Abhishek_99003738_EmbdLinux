obj-m += iPC_task.o
KSRC = /home/user/elinux/kernel_ws/linux-4.14.227

all:
	make -C ${KSRC} M=${PWD} ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

clean:
	make -C ${KSRC} M=${PWD} clean
