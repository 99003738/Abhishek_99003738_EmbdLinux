
#include <unistd.h>
#include <stdio.h>
//#include <linux/kernel.h>
//#include <linux/fs.h
//#include <asm/uaccess.h>
//#include <linux/buffer_head.h>
#include <sys/file.h>

int main(){

int fd , nbytes;
char buf[64];
int maxlen=64;

fd=open("/dev/psample", O_RDWR);

if(fd<0) {
perror("open");
}
char str[]="abcdxyz";
nbytes=write(fd,str,7);
printf("nbytes %d",nbytes);
if(nbytes<0) {
perror("write");
}

nbytes=read(fd,buf,maxlen);
printf("nbytes %d",nbytes);
if(nbytes<0) {
perror("write");
}
write(1,buf,maxlen);
buf[nbytes]='\0';
puts(buf);
close(fd);
}
