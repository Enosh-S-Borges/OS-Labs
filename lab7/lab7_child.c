/*Write  a  program  to  generate  and  print  Prime  numbers  between  a  given range(between M & N) with the following requirements 
 - M& N should be passed as command line arguments 
 - Error checking should be done to verify the required number of arguments at the command line 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Prime numbers to its child. 
 - The code for generating Prime numbers should reside in different program. 
 -  Child  should  write  the  generated  Prime  numbers  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Prime  numbers from the shared memory. 
Implement the above using shm_open and mmap 
Note: Shared object should be removed at the end in the program.*/

// i) Child Program:
/*Execute as:
gcc parent.c -lrt -o parent
gcc child.c -lrt -lm -o child
./parent (input a) (input b)*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <math.h>

int main(int argumentCount, char *argumentVector[]) {
    void *ptr;
    int sharedMemoryFileDescriptor = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(sharedMemoryFileDescriptor, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, sharedMemoryFileDescriptor, 0);

    printf("CHILD:\n");

    int i = atoi(argumentVector[1]);
    int j = atoi(argumentVector[2]);
    int flag = 0;

    printf("The prime numbers in the range %d and %d are:\n", i, j);

    for (int num = i; num < j; num++) {
        flag = 0;
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            sprintf(ptr, "%d\t", num);   // Write to shared memory
            ptr += strlen((char*)ptr);   // Move pointer forward
            printf("%d\t", num);
        }
    }
    printf("\n");
    shm_unlink("VSS");   // Optional cleanup in child (better in parent)
    return 0;
}