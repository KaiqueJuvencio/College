#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
  long long int max, idThread, lenVector, sum;
  lenVector = 107374182;
  long long int *vector = (long long int *)(malloc(lenVector * sizeof(long long int)));

  for(long long int i = 0; i < lenVector; i++){ //Preenche todo o vetor com 1
    vector[i] = 1;
  }

  max = omp_get_max_threads();
  printf("Threads: %lld\n", max);
  
#pragma omp parallel private(idThread)
{
  idThread = omp_get_thread_num();
  
  #pragma omp for reduction(+: sum)
  for(long long int  i = 0; i < lenVector; i++){
    sum += vector[i];
  }
  printf("Thread %lld sum %lli\n",idThread, sum);  
}
  return 0;
}
