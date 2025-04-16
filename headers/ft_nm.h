#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include <elf.h>
#include <stdbool.h>
#include "../libft/libft.h"

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"


typedef struct s_symbol {
    const Elf64_Sym *symTab;
    char name[255];
} t_symbol;

int open_file(char *pathfile);
int get_file_size(int fd);

int ft_nm(char *filepath);