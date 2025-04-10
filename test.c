#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void) {
    int fd = open("test.c", O_RDONLY);
    if (fd == -1) {
        puts("Can't open file");
        exit(1);
    }
    struct stat st;
    fstat(fd, &st);
    int size = st.st_size;
    printf("File size = %d\n", size);

    return 0;
}