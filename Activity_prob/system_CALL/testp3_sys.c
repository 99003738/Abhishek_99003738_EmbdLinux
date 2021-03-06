
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>


#define listProcessInfo 404

int main()
{  
    printf("Invoking 'listProcessInfo' system call");
         
    long int ret_status = syscall(listProcessInfo); // 404 is the syscall number
         
    if(ret_status == 0) 
         printf("System call 'listProcessInfo' executed correctly. Use dmesg to check processInfo\n");
    
    else 
         printf("System call 'listProcessInfo' did not execute as expected\n");
          
     return 0;
}
