#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
  long long int max, idThread, lenVector, sum;
  sum = 0;
  lenVector = 107374182;
  long long int *vector = (long long int *)(malloc(lenVector * sizeof(long long int)));

  for(long long int i = 0; i < lenVector; i++){ //Preenche todo o vetor com 1
    vector[i] = 1;
  }

  max = omp_get_max_threads();
  printf("Threads: %lld\n", max);
  
#pragma omp parallel private(idThread, sum)
{
  idThread = omp_get_thread_num();
  long long int begin = idThread * lenVector/max;
  long long int finish = begin + lenVector/max;
  
  printf("%lli  %lli \n", begin, finish);
  for(long long int  i = begin; i < finish; i++){
    #pragma omp critical
    sum += vector[i];
  }
  printf("Thread %lld sum %lli\n",idThread, sum);  
}
  return 0;
}
