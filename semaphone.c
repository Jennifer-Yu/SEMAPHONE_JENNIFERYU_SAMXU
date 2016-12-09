//Jennifer Yu
//12-07-16

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

int main(int argc, char* argv[]) {
  int semid;
  int shmid;
  int key = ftok("makefile", 5);
  int sc;
  union semun su;
  
  if (strncmp(argv[1], "-c", strlen(argv[1])) == 0) {
    shmid = shmget(key, 16384, IPC_CREAT | 0644);
    semid = semget(key, 1, IPC_CREAT | 0644);
    if (semid >= 0) { 
      printf("semaphore created: %d\n", semid);
      su.val = 1;
    }
    else {
      printf("sem exists");
    }
  }

  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0) {
    semid = semget(key, 1, 0);
    int i = semctl(semid, 0, GETVAL);
    printf("semaphore value: %d\n", i);
  }
  
  else if ( strncmp(argv[1], "-r", strlen(argv[1]) ) == 0) {
    semid = semget(key, 1, 0);
    shmid = shmget(key, 1, 0);
    int i = semctl(semid, 0, IPC_RMID);
    printf("semaphore removed: %d\n", i);
    i = shmctl(shmid, IPC_RMID, 0);
    printf("shared memory removed: %d\n", i);
    printf("shmid: %d\n", shmid);
  }
    
  return 0;

}
