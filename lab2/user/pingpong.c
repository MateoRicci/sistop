#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int search_sem(int value){
    int sem = 0;
    int res = sem_open(sem, value);
    while(res==0){
        sem ++;
        res = sem_open(sem, value);
    }
    return sem;
}

void ping(int sem1, int sem2, int count){
    for(unsigned int i = 0; i < count; i++){
        sem_down(sem1);         //baja ping
        printf("ping\n");       //print
        sem_up(sem2);           //sube pong
    }
}

void pong(int sem2, int sem1, int count){
    for(unsigned int i = 0; i < count; i++){
        sem_down(sem2);         //baja pong
        printf("\tpong\n");   //print
        sem_up(sem1);           //sube ping
    }
}

int 
main(int argc,char* argv[]) 
{
    if (argc != 2){     //chequeo que solo haya dos argumentos 
        printf("ERROR: cantidad de argumentos no valida\n");
        exit(1);
    }
    int count= atoi(argv[1]);

    if (count < 1){
        printf("ERROR: argumento invalido\n");
        exit(1);
    }
    
    //inicializo semaforos
    int sem1 = search_sem(1);                       //open sem 1
    int sem2 = search_sem(0);                       //open sem 2

    int pid = fork();

    if (pid < 0) {          //si fork < 0 error
            printf("ERROR: fork failed\n");
            exit(1);
        }

    else if(pid == 0){           //proceso hijo
        ping(sem1,sem2, count);
    } 

    else if (pid > 0) {   //proceso padre
        pong(sem2,sem1, count);
        sem_close(sem1);
        sem_close(sem2);
    }

    wait(&pid);
    exit(1);
} 