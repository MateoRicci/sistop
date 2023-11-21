#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//example syscall -> return 2023
uint64
sys_example(void){
  return(2023);
}

// semaforo
#define SEMSIZE 512

/*
struct semaphores_t{
  int value; // valor del semaforo
  int open; // 1 abierto, 0 cerrado, else error
  struct spinlock *lock; // locker?
};

struct semahore_t* semaphores[SEMSIZE];
*/

struct semaphore_t{
  int value; // valor del semaforo
  int is_free; // 1 abierto, 0 cerrado, else error
  struct spinlock lock; // locker?
};

struct semaphore_t semaphores[SEMSIZE];

struct spinlock open_lock;

void seminit(void){
  initlock(&open_lock, "open_lock");
  for(unsigned int i=0; i < SEMSIZE; i++){
    semaphores[i].is_free=1;
    initlock(&semaphores[i].lock,"sem_lock");
  }
}
/*
int search_sem(void){
  int res = -1; // retorna -1 si todos los sem estan llenos
  for(int i = 0;i<SEMSIZE;i++){
    if(semaphores[i].open == 1){
      res = i;
      break;
    }
  }
  return res;
} */
int check_sem(int sem){
  int res = 0;
  if(sem<0||sem>SEMSIZE){
    res = -1;
  }
  acquire(&open_lock);
  if(semaphores[sem].is_free==1){
    res = semaphores[sem].is_free;
    semaphores[sem].is_free = 0;
  }
  release(&open_lock);
  return res;
}

//Abre y/o inicializa el semáforo “sem” con  un valor arbitrario “value”. 
uint64
sys_sem_open(void){

  int sem;
  int value;
  argint(0,&sem);
  argint(1,&value);

  if(check_sem(sem)==1){
  acquire(&semaphores[sem].lock);

  semaphores[sem].value = value;
  
  release(&semaphores[sem].lock);

  return 1;
  }
  return 0;
}

//Libera el semáforo “sem”. 
uint64
sys_sem_close(void){
  int sem;
  argint(0,&sem);

  acquire(&semaphores[sem].lock);

  semaphores[sem].is_free=1;

  release(&semaphores[sem].lock);

  return 0;
}

//Incrementa el semáforo ”sem” desbloqueando los procesos cuando su valor es 0. 
uint64
sys_sem_up(void){
  int sem;
  argint(0,&sem);

	if(semaphores[sem].value<0 || semaphores[sem].value>=SEMSIZE){
		return 0;
	} 

  acquire(&semaphores[sem].lock);

  if(semaphores[sem].value == 0){
		wakeup(&semaphores[sem]);
	}
	semaphores[sem].value++;

  release(&semaphores[sem].lock);

	return 1;
}

uint64
sys_sem_down(void){
  int sem;
  argint(0,&sem);

  if(semaphores[sem].value<0 || semaphores[sem].value>=SEMSIZE){
		return 0;
	} 

  acquire(&semaphores[sem].lock);

  while(semaphores[sem].value == 0){
		sleep(&semaphores[sem], &semaphores[sem].lock);
	}
	semaphores[sem].value--;

  release(&semaphores[sem].lock);

	return 0;
}
