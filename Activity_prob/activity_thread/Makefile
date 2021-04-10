obj-m += kthread_fifo.o
KSRC = /home/user/elinux/KSRC/linux-4.14.227

all:
	make -C ${KSRC} M=${PWD} ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

clean:
	make -C ${KSRC} M=${PWD} clean
