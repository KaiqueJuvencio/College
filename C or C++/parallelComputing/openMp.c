#include <stdio.h>
#include <omp.h>

int main(){
  int max, idThread, k, findElement;
  int tamVetor = 65536;
  int vetor[tamVetor];

  max = omp_get_max_threads();
  printf("Threads: %d\n", max);
  findElement = 65010;

  for(k=0; k<tamVetor; k++){  //preenche vetor
    vetor[k] = k;
  }
#pragma omp parallel private(idThread)
{
  idThread = omp_get_thread_num();
  printf("Thread ID: %d\n", idThread);
    
  for (k=idThread; k<tamVetor; k=k+(max)){
    if(findElement == vetor[k]){
        printf("Elemento encontrado na posicao: %d\n", k);
    }
  }

}
  return 0;
}
