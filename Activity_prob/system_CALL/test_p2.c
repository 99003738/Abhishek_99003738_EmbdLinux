#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define test2sys  403

int main()
{

long int ret;
  ret = syscall(test2sys);
  if (ret<0)
  {
  printf("systemcall failed");
  }
  printf("system called passed");

}
