#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    assert(setlocale(LC_MESSAGES, "en_US.UTF-8") != NULL);

    int fd = open("memory-mapped-io/assets/hello-world.txt", O_RDWR);
    if (fd == -1) {
        fprintf(
            stderr,
            "io error: unable to open the input file (%s)\n",
            strerror(errno)
        );
        goto OPEN_FAILED;
    }

    struct stat fd_stats = {0};
    if (fstat(fd, &fd_stats) == -1) {
        fprintf(
            stderr,
            "information error: unable to get the size of the input file (%s)\n",
            strerror(errno)
        );
        goto FSTAT_FAILED;
    }

    char *file_in_memory = mmap(
        NULL,
        (size_t)fd_stats.st_size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
    if (file_in_memory == MAP_FAILED) {
        fprintf(
            stderr,
            "memory mapping error: unable to map the input file into memory (%s)\n",
            strerror(errno)
        );
        goto MMAP_FAILED;
    }

    printf("Before: ");
    for (size_t i = 0; i < (size_t)fd_stats.st_size; i++) {
        putchar(file_in_memory[i]);
        if (isupper(file_in_memory[i])) {
            file_in_memory[i] = (char)tolower(file_in_memory[i]);
        }
        else if (islower(file_in_memory[i])) {
            file_in_memory[i] = (char)toupper(file_in_memory[i]);
        }
    }

    if (msync(file_in_memory, (size_t)fd_stats.st_size, MS_SYNC | MS_INVALIDATE) == -1) {
        fprintf(
            stderr,
            "memory mapping error: unable to flush the mapped memory back into the input file (%s)\n",
            strerror(errno)
        );
        goto MSYNC_FAILED;
    }

    printf("After: ");
    for (size_t i = 0; i < (size_t)fd_stats.st_size; i++) {
        putchar(file_in_memory[i]);
    }

    munmap(file_in_memory, (size_t)fd_stats.st_size);
    close(fd);
    return EXIT_SUCCESS;


    MSYNC_FAILED:
    munmap(file_in_memory, (size_t)fd_stats.st_size);

    MMAP_FAILED:

    FSTAT_FAILED:
    close(fd);

    OPEN_FAILED:

    return EXIT_FAILURE;
}
