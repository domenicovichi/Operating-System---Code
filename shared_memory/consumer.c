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
    const int SIZE = 4096;                                     // shared memory segment size
    const char *name = "SHM";                                  // segment name
    int shm_fd;                                                // shared memory file descriptor
    void *shm_ptr;                                             // shared memory pointer
    shm_fd = shm_open(name, O_RDONLY, 0666);                   // read segment access
    shm_ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); // memory map
    printf("%s", (char *)shm_ptr);
    shm_unlink(name); // removal of shared memory segment
    return 0;
}