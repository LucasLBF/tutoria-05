#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int result = 0;
void *increment(void *matrix);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct args {
  int matrixOrder;
  int *matrixLine;
};

int main(void) {
  int matrixOrder = 0;
  int current = 0;
  scanf("%d", &matrixOrder);
  int matrix[matrixOrder][matrixOrder];
  pthread_t threads[matrixOrder];

  for (int i = 0; i < matrixOrder; i++) {
    for (int j = 0; j < matrixOrder; j++) {
      scanf("%d", &current);
      matrix[i][j] = current;
    }
  }

  for (int i = 0; i < matrixOrder; i++) {
    struct args *a = (struct args *)malloc(sizeof(struct args));
    a->matrixOrder = matrixOrder;
    a->matrixLine = (int *)malloc(matrixOrder * sizeof(int));
    for (int j = 0; j < matrixOrder; j++) {
      a->matrixLine[j] = matrix[i][j];
    }
    pthread_create(&(threads[i]), NULL, increment, (void *)a);
  }

  for (int i = 0; i < matrixOrder; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("%d\n", result);
  return 0;
}

void *increment(void *a) {
  struct args *args = (struct args *)a;
  int matrixOrder = args->matrixOrder;
  int lineSum = 0;

  for (int i = 0; i < matrixOrder; i++) {
    lineSum += args->matrixLine[i];
  }
  pthread_mutex_lock(&mutex);
  result += lineSum;
  pthread_mutex_unlock(&mutex);
  return a;
}
