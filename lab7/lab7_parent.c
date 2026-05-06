/*Write  a  program  to  generate  and  print  Prime  numbers  between  a  given range(between M & N) with the following requirements 
 - M& N should be passed as command line arguments 
 - Error checking should be done to verify the required number of arguments at the command line 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Prime numbers to its child. 
 - The code for generating Prime numbers should reside in different program. 
 -  Child  should  write  the  generated  Prime  numbers  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Prime  numbers from the shared memory. 
Implement the above using shm_open and mmap 
Note: Shared object should be removed at the end in the program.*/

// i) Parent Program:
/*Execute as:
gcc parent.c -lrt -o parent
gcc child.c -lrt -lm -o child
./parent (input a) (input b)*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argumentCount, char *argumentVector[]) {
    int i, j, sharedMemoryFileDescriptor;
    const int SIZE = 4096;
    pid_t processID;
    void *ptr;

    if (argumentCount > 2) {
        sscanf(argumentVector[1], "%d", &i);
        sscanf(argumentVector[2], "%d", &j);
        if (i < 2) {
            printf("Error input: %d\n", i);
            return 0;
        }
    } else {
        printf("Error: Minimum of two arguments must be passed as command line arguments!\n");
        exit(0);
    }

    processID = fork();

    if (processID == 0) {
        execl("./child", "prime", argumentVector[1], argumentVector[2], NULL);
    } else if (processID > 0) {
        wait(NULL);
        printf("\nParent: child completed!\n");

        sharedMemoryFileDescriptor = shm_open("VSS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, sharedMemoryFileDescriptor, 0);

        printf("%s", (char *)ptr);
        shm_unlink("VSS");
    }
    return 0;
}