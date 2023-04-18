// We develop communication between processes with the use of shared memory. Let's take a producer-consumer example

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    const int SIZE = 4096; // shared memory segment size
    const char *name = "SHM";

    void *shm_ptr; // shared memory segment pointer
    const char *string_0 = "Hello";
    const char *string_1 = "Everyone ";
    int shm_fd; // shared memory file descriptor

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);            // create segment
    ftruncate(shm_fd, SIZE);                                    // dimension the segment
    shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); // segment memory map
    sprintf(shm_ptr, "%s", string_0);                           // write in segment
    shm_ptr += strlen(string_0);
    sprintf(shm_ptr, "%s", string_1);
    shm_ptr += strlen(string_1);
    return 0;
}