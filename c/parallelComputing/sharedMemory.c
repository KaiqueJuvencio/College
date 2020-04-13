#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void  ClientProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     if (argc != 5) {
          printf("Use: %s #1 #2 #3 #4\n", argv[0]);
          exit(1);
     }

     ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);//identificador do segmento de memória compartilhada shmid, ou -1 em caso de erro.
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }

     ShmPTR = (int *) shmat(ShmID, NULL, 0);//endereço do segmento de memória compartilhada, ou -1 em caso de erro.
     if ((int) ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }

     ShmPTR[0] = atoi(argv[1]);
     ShmPTR[1] = atoi(argv[2]);
     ShmPTR[2] = atoi(argv[3]);
     ShmPTR[3] = atoi(argv[4]);
     printf("Pai: Foi preenchido %d %d %d %d na memória compartilhada...\n",
            ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);

     pid = fork();//Cria filho
     
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid > 0) {
          printf("Pai: Espera o filho ser executado\n");
          wait(&status);
     }
     else if (pid == 0) {
          printf("Filho: Começa a ser executado\n");
          ClientProcess(ShmPTR);
          exit(0);
     }
  
      printf("Pai: Achou %d %d %d %d na memória compartilhada\n",
                ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);
    printf("Pai: Modifica a memória compartilhada multiplicando tudo por 2\n"); 
    ShmPTR[0] = ShmPTR[0]*2;
    ShmPTR[1] = ShmPTR[1]*2;
    ShmPTR[2] = ShmPTR[2]*2;
    ShmPTR[3] = ShmPTR[3]*2;

    printf("Pai: Achou %d %d %d %d na memória compartilhada\n",
          ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);
    
     shmdt((void *) ShmPTR); 
     shmctl(ShmID, IPC_RMID, NULL);//Destrói a área de memória
     printf("Pai: Destruiu a memória compartilhada...\n");
    
     exit(0);
}

void  ClientProcess(int  SharedMem[])
{
     printf("Filho: Achou %d %d %d %d na memória compartilhada\n",
                SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3]);
     printf("Filho: Modifica a memória compartilhada multiplicando tudo por 2\n");
    SharedMem[0] = SharedMem[0]*2;
    SharedMem[1] = SharedMem[1]*2;
    SharedMem[2] = SharedMem[2]*2;
    SharedMem[3] = SharedMem[3]*2;
}