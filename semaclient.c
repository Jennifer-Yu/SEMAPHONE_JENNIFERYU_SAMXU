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

void semU(int semid){
  struct sembuf operation;
  operation.sem_op = 1;
  operation.sem_num = 1;
  operation.sem_flg = SEM_UNDO;
  semop(semid, &operation, 1);
}

void semD(int semid){
  struct sembuf operation;
  operation.sem_op = -1;
  operation.sem_num = 1;
  operation.sem_flg = SEM_UNDO;
  semop(semid, &operation, 1);
}

void pLine(int *shm){
  int fd;
  int temp = * shm;
  char buf[temp + 1];
  
  fd = open("story.txt", O_RDONLY, 0644);
  lseek(fd, (-1 * temp), SEEK_END);
  read(fd, &buf, temp);
  buf[temp] = 0;
  printf("Previous line:\n");
  printf("%s\n", buf);
  close(fd);
}

void getAddLine(int *shm){
  char buf[1024];
  char * dest = buf;
  int fd;
  int len;

  printf("Enter next line: ");
  fgets(dest, 1024, stdin);
  
  len = strlen(buf);
  *shm = len;
  
  fd = open("story.txt", O_WRONLY | O_APPEND, 0644);
  
  write(fd, buf, len);
  close(fd);

  printf("added line: %s\n", buf);
}

int main() {
  int key = ftok("makefile",5);
  int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
  semD(semid);
  int shmid = shmget(key, 4, 0644);
  int *len = shmat(shmid, 0, 0);
  semU(semid);
  pLine(len);
  getAddLine(len);
  
  
  return 1337;
}
