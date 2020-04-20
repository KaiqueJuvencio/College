#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
  long long int max, idThread, lenVector;
  lenVector = 107374182;
  long long int *vector = (long long int *)(malloc(lenVector * sizeof(long long int)));

  for(long long int i = 0; i < lenVector; i++){ //Preenche todo o vetor com 2
    vector[i] = 1;
  }

  max = omp_get_max_threads();
  printf("Threads: %lld\n", max);
 
  long long int *tempMemory = (long long int *)(malloc(lenVector * sizeof(long long int)));
  
#pragma omp parallel private(idThread)
{
  long long int sum = 0;
  idThread = omp_get_thread_num();
  long long int begin = idThread * lenVector/max;
  long long int finish = begin + lenVector/max;
  
  printf("%lli  %lli \n", begin, finish);
  for(long long int  i = begin; i < finish; i++){
    sum += vector[i];
  }
  tempMemory[idThread] = sum;
  printf("Thread %lld sum %lli\n",idThread, sum);  
} 
  long long int total = 0;
  for(long long int i = 0; i < max; i++){
    total += tempMemory[i];
  }
  
  printf("Total: %lli", total);
  return 0;
}
