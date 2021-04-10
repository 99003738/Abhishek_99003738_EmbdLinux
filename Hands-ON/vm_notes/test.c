#include<unistd.h>
#include<sys/mman.h>

#define MAP_SIZE 2096

int main() 
{
  int fd=-1,i;
  char* pbase;
  pbase=mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE,
			   MAP_PRIVATE|MAP_ANONYMOUS, fd, 0);
  if(pbase==NULL)
    perror("mmap");

  for(i=0;i<100;i++)
    *(pbase+i)=rand()%256;

  munmap(pbase, MAP_SIZE);
  return 0;
}

