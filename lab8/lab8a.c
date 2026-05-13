/* 8. a) Write a program with two threads and a main thread.
Schedule the task of calculating the natural sum upto 'n' terms and factorial of 'n' of these threads. 
NOTE: The main thread should read 'n' from command line and pass it as parameter to remaining threads. Terminate the threads using system calls. 
b) Implement FCFS scheduling algorithm by defining the process structure. 
*/
// gcc thread.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *sum(void *arg);
void *mul(void *arg);

int sm = 0, prod = 1;

void *sum(void *parm) {
    int i, n;
    n = atoi(parm);
    printf("inside sum thread\n");
    for(i = 1; i <= n; i++) {
        sm += i;
    }
    printf("sum thread completed\n");
    return NULL;
}

void *mul(void *parm) {
    int i, n;
    n = atoi(parm);
    printf("inside mul thread\n");
    for(i = 2; i <= n; i++) {
        prod = prod * i;
    }
    printf("mul thread completed product\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t T1, T2;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    
    pthread_create(&T1, &attr, sum, argv[1]);
    pthread_create(&T2, &attr, mul, argv[1]);
    
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);
    
    printf("Inside main thread\n");
    printf("sum=%d\n", sm);
    printf("Factorial=%d\n", prod);
    
    return 0;
}
