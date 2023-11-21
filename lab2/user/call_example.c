#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int 
main(void) 
{
    printf("Llamada a syscall example (muestra 2023): %d\n", example());

    //printf("Llamada a syscall semopen (muestra 1): %d\n", sem_open());

    //printf("Llamada a syscall semclose (muestra 1001): %d\n", sem_close());

    //printf("Llamada a syscall semup (muestra 1002): %d\n", sem_up());

    //printf("Llamada a syscall semdown (muestra 1003): %d\n", sem_down());
    
    exit(1);
} 