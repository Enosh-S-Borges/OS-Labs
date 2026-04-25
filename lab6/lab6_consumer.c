/*LAB 6: Write a program to generate and print Fibonacci series with the following requirements: 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Fibonacci series to its child. 
 - The code for generating Fibonacci series should reside in different program. 
 -  Child  should  write  the  generated  Fibonacci  series  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Fibonacci  series from the shared memory. 
Implement the above using shmget and shmat 
Note: Shared object should be removed at the end in the program. */

// ii) Consumer program

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    void *psm;
    int shmid;

    shmid = shm_open("dsaygdsik", O_RDONLY, 0666);
    ftruncate(shmid, 1024);

    psm = mmap(0, 1024, PROT_READ, MAP_SHARED, shmid, 0);

    printf("Key/ID of the shared memory: %d\n", shmid);
    printf("Shared memory for consumer attached at %p\n", psm);

    printf("Data read from shared memory: %s\n", (char *)psm);

    shm_unlink("dsaygdsik");

    return 0;
}