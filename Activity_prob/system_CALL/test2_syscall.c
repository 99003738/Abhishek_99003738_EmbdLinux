#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <string.h>
int main(void){
	
    char st[256];
    sprintf(st, "hello kernel!");
    
    long sta = syscall(402, st, 20);

}
