/*LAB 6: Write a program to generate and print Fibonacci series with the following requirements: 
 -  Parent  program  should  create  a  child  and  distribute  the  task  of generating Fibonacci series to its child. 
 - The code for generating Fibonacci series should reside in different program. 
 -  Child  should  write  the  generated  Fibonacci  series  to  a  shared memory. 
 -  Parent  process  has  to  print  by  retrieving  the  Fibonacci  series from the shared memory. 
Implement the above using shmget and shmat 
Note: Shared object should be removed at the end in the program. */

// i) Producer program

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
    void *psm;
    char buf[10];
    int shmid;

    shmid = shm_open("dsaygdsik", O_CREAT | O_RDWR, 0666);
    ftruncate(shmid, 1024);

    psm = mmap(0, 1024, PROT_WRITE, MAP_SHARED, shmid, 0);

    printf("Key/ID of the shared memory: %d\n", shmid);
    printf("Shared memory attached at %p\n", psm);

    printf("Enter some data to write to shared memory: ");
    read(0, buf, 10);

    sprintf(psm, "%s", buf);

    return 0;
}