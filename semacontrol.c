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

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

int openFile(){
  int fd;
  if( access( "story.txt", F_OK ) != -1 ) {
    fd = open("story.txt", O_RDWR | O_TRUNC);
  }
  else{
    fd = open("story.txt", O_RDWR | O_CREAT, 0644);
  }
  printf("File opened, file descriptor: %d\n",fd);
  return fd;
}

int main(int argc, char* argv[]) {
  int semid;
  int shmid;
  int key = ftok("makefile", 5);
  int sc;
  int fd = openFile();
  struct shmid_ds d;
  union semun su;
  
  if (strncmp(argv[1], "-c", strlen(argv[1])) == 0) {
    //Creating semaphore
    semid = semget(key, 1, IPC_CREAT | 0644);
    if(semid >= 0){
      printf("semaphore created: %d\n", semid);
    }else{
      printf("Error: unable to create semaphore");
    }

    su.val = 10;
    //Setting sempahore
    sc = semctl(semid, 0, SETVAL, su);
    printf("Semaphone value set: %d\n",sc);

    //Creating shared mem
    shmid = shmget(key, 8, IPC_CREAT | 0644);
    if(shmid >= 0){
      printf("shm created: %d\n", shmid);
    }else{
      printf("Error: unable to create shm");
    }
  }
  
  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0) {
    char buf[256];
    printf("Finding %ld\n", lseek(fd,0, SEEK_SET));
    read(fd, buf, 256);
    printf("%s\n",buf);
  }
  
  else if ( strncmp(argv[1], "-r", strlen(argv[1]) ) == 0) {
    //removing sempahore
    semid = semget(key,1,0);
    sc = semctl(semid, 0 , IPC_RMID);
    printf("removed semaphore: %d\n",sc);

    //removing shm
    shmid = shmget(key, 0, 0);
    shmctl(shmid, IPC_RMID, &d);
    printf("removed shm: %d\n", shmid);

    close(3);
  }
    
  return 0;

}
