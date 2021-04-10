#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 64
int main()
{
  int fd,nbytes;
  fd=open("/dev/psample0",O_RDWR);
  if(fd<0)
  {
     perror("open");
  }
  char wbuf[SIZE];
  char wbuf2[SIZE] ;
  
  //memset(wbuf, 0, SIZE*sizeof(char)); 
  wbuf[SIZE]= "where I am";
  nbytes=write(fd,wbuf,SIZE);
  
  if(nbytes<0)
  {
    perror("write");
  }
  
   //memset(wbuf2, 0, SIZE*sizeof(char)); 
   wbuf2[SIZE]= "you are in thread 2";
   nbytes=write(fd,wbuf2,SIZE);
  
  char rbuff[SIZE];
  while(1)
  {
    nbytes=read(fd,rbuff,10);
    if(nbytes < 0)
    {
        perror("read");
    } 
    if(nbytes == 0)
    {
       break;
    }
    rbuff[nbytes]='\0';
    printf("\n%s nbytes=%d", rbuff,nbytes);
  }
  
   
  
  
  
  close(fd);
  return 0;
}
