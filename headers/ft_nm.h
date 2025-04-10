#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include <elf.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define E_SHOFF_OFFSET_32_BITS 0x20
#define E_SHOFF_OFFSET_64_BITS 0x28
#define E_SHOFF_32_BITS_SIZE 4
#define E_SHOFF_64_BITS_SIZE 8


int open_file(char *pathfile);
int get_file_size(int fd);
int allocate_file_buffer(char **buf, int file_size);
int read_file(int fd, char **buf, int file_size);

int ft_nm(char *filepath);