//Jennifer Yu and Sam Xu
//12-07-16

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

int main() {
  int semid;
  int shmid;
  int key = ftok("makefile", 5);

  shmid = shmget(key,0,IPC_ACCESS);
				    

  
  return 1337;
}
