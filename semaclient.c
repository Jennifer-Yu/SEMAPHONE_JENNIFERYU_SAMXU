//Jennifer Yu and Sam Xu
//12-07-16

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


union semun{
  int val;
  struct semi_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

int main() {
  int key = ftok("makefile",5);
  int semid = semget(key, 1, 0);
  int shmid = shmget(key, 1, 0);
  int *len = shmat(shmid, 0, 0);

  char fbuf[*len + 50];
  int fd;
  union semun su;
				    
  int val = semctl(semid, 0, GETVAL, su);

  
  return 1337;
}
