/*LAB 6: Write a program to generate and print Fibonacci series with the following requirements: 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Fibonacci series to its child. 
 - The code for generating Fibonacci series should reside in different program. 
 -  Child  should  write  the  generated  Fibonacci  series  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Fibonacci  series from the shared memory. 
Implement the above using shmget and shmat 
Note: Shared object should be removed at the end in the program. */

// ii) Child program

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int shmid = atoi(argv[1]);
    int n = atoi(argv[2]);

    int *arr = (int *) shmat(shmid, NULL, 0);

    int a = 0, b = 1, c;

    arr[0] = a;
    arr[1] = b;

    for(int i = 2; i < n; i++)
    {
        c = a + b;
        arr[i] = c;
        a = b;
        b = c;
    }

    shmdt(arr);
    return 0;
}