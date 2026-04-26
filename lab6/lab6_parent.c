/*LAB 6: Write a program to generate and print Fibonacci series with the following requirements: 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Fibonacci series to its child. 
 - The code for generating Fibonacci series should reside in different program. 
 -  Child  should  write  the  generated  Fibonacci  series  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Fibonacci  series from the shared memory. 
Implement the above using shmget and shmat 
Note: Shared object should be removed at the end in the program. */

// i) Parent program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int n;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    int shmid = shmget(IPC_PRIVATE, n * sizeof(int), 0666 | IPC_CREAT);

    int *arr = (int *) shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if(pid == 0)
    {
        // Child → execute Fibonacci program
        char shm_str[10], n_str[10];

        sprintf(shm_str, "%d", shmid);
        sprintf(n_str, "%d", n);

        execl("./lab6_child", "lab6_child", shm_str, n_str, NULL);

        perror("exec failed");
        exit(1);
    }
    else
    {
        wait(NULL);

        printf("Fibonacci series:\n");

        for(int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\n");

        shmdt(arr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}