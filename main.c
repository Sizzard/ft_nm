#include "headers/ft_nm.h"

int iiiiiiiiiiiiiiiii = 0;
int ___data_start = 0;

int file_size = 0;

int ft_nm(char *filepath) {
    uint8_t *file = NULL;
    int fd = 0;
    bool return_value;

    fd = open(filepath, R_OK);
    // printf("fd : %d\n", fd);
    if (fd == -1) {
        ft_printfd(2, "%s: Can't open file\n", filepath);
        return 1;
    }
    
    file_size = get_file_size(fd);
    if (file_size == -1 || file_size == 0 || file_size <= 16) {
        ft_printfd(2, "%s: Not a valid file\n", filepath);
        return 1;
    }

    // printf("File size : %d\n", file_size);

    file = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    close(fd);

    if (is_valid_elf_file(file) == false) {
        ft_printfd(2, "%s: file format not recognized\n", filepath);
        munmap(file, file_size);
        return 1;
    }

    // print_file_content(file);

    if (file[4] == 1) {
        return_value = handle_32_files(file);
    }
    else {
        return_value = handle_64_files(file);
    }

    munmap(file, file_size);
    
    return return_value;
}

int main(int ac, char **av) {

    int return_value = 0;

    if (ac == 1) {
        return_value = ft_nm("a.out");
    }
    else {
        for(int i = 1; av[i]; i++) {
            if (ac > 2) {
                ft_printfd(1, "\n%s:\n", av[i]);
            }
            const int tmp_value = ft_nm(av[i]);
            if (tmp_value != 0) {
                return_value = tmp_value;
            }
        }
    }

    return return_value;
}