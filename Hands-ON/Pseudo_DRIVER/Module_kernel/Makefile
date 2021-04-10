obj-m += hello.o helloModule.o moduleDependency_Simple.o moduleDependency_Sample.o moduleParameter.o
KSRC = /home/user/embdLinux/kernel_build/KSRC
#make -C ${KSRC} M=${PWD} modules
#ARCH = arm,
#CROSS_COMPILE=arm-linux-gnueabi-gcc

all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

clean:
	make -C ${KSRC} M=${PWD} clean
