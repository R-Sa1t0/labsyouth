#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *threadfunc(void* arg) {
  puts("Hello! pthread!! - 1");
  sleep(1);
  puts("Hello! pthread!! - 2");
  return NULL;
}

int main(void) {
  pthread_t thread;
  if (pthread_create(&thread, NULL, threadfunc, NULL) != 0)
    exit(1);
  
  printf("Hello!!\n");

  if (pthread_join(thread, NULL) != 0)
    exit(2);
}