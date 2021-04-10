
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>


int main(int argc, char **argv)
{
    printf("1 : %ld\n", syscall(400));
    //printf("2 : %ld\n", syscall(401, 1));
    //printf("3 : %ld\n", syscall(402, 2, 3));
    if (argc <= 1) {
    printf("Must provide a string to give to system call.\n");
    return -1;
  }
  char *arg = argv[1];
  printf("Making system call with \"%s\".\n", arg);
  long res = syscall(401, arg);
  long res1 = syscall(402, arg);
  printf("System call returned %ld.\n", res);
  return res;
    
    char st[256];
    sprintf(st, "hello kernel!");
    
    long sta = syscall(402, st, 20);
    
    return 0;
}

