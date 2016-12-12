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

int getSize(){
  struct stat fileIn;
  stat("story.txt", &fileIn);
  return fileIn.st_size;
}

void printStory(){
  int len = getSize();
  printf("len: %d\n", len);
  char buf[len + 25];
  
  int fd = open("story.txt", O_RDONLY, 0644);
  read(fd, &buf, getSize());
  buf[len] = 0;
  
  printf("Story: %s\n", buf);
  close(fd);
}

int main(int argc, char* argv[]) {
  int semid;
  int shmid;
  int key = ftok("makefile", 5);
  int sc;
  int fd;
  int *shm;
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
    shm = shmat(shmid, 0, 0);
    *shm = 0;

    //setting up file
    int fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
    close(fd);
  }
  
  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0) {
    printStory();
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

    printStory();
    int fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
    close(fd);
  }else{
    printf("No arguments. Use -c for create, -v for view, -r for remove.\n");
  }
    
  return 0;

}
