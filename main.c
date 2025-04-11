#include "headers/ft_nm.h"

int iiiiiiiiiiiiiiiii = 0;

int open_file(char *pathfile) {
    int fd = open(pathfile, O_RDONLY);
    if (fd == -1) {
        ft_putstr_fd("Can't open file", 2);
        return -1;
    }
    return fd;
}

int get_file_size(int fd) {
    struct stat st;
    fstat(fd, &st);
    return st.st_size;
}

int find_symtab(uint8_t *file, const Elf64_Ehdr *eHdr, const char *shStrTab_data) {
    for (int i = 0; i < eHdr->e_shnum; i++) {
        const Elf64_Shdr *sHdr = (Elf64_Shdr *)(file + eHdr->e_shoff + (64 * i));
        const char *section_name = shStrTab_data + sHdr->sh_name;
        printf(" [%2d] : %s\n", i, section_name);
        if (ft_strncmp(section_name, ".symtab", ft_strlen(".symtab")) == 0) {
            printf("%s found at index %d\n", section_name, i);
            return i;
        }
    }
    return -1;
}

void print_all_symbols(uint8_t *file, const Elf64_Ehdr *eHdr, int symtabNdx) {

    const Elf64_Shdr *symTab = (Elf64_Shdr *)(file + eHdr->e_shoff + (64 * symtabNdx));
    
    const Elf64_Sym *effectiveSymTab = (Elf64_Sym *)(file + symTab->sh_offset);

    printf("number of symbols : 0x%08lx\n", effectiveSymTab->st_size / sizeof(Elf64_Sym));

    // write(1, &file[symTab_data], 500);

    // for (int i = 0; ;i++) {

    // }
}

int ft_nm(char *filepath) {
    uint8_t *file = NULL;
    int fd = 0;
    int file_size = 0;

    fd = open_file(filepath);
    printf("fd : %d\n", fd);
    if (fd == -1) {
        return 1;
    }
    
    file_size = get_file_size(fd);

    printf("File size : %d\n", file_size);

    file = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    close(fd);

    for(int i = 0; i < file_size; i++) {
        if (file[i] == 0) {
            printf("%s%02X %s", BLK, file[i], WHT);
        }
        else if (file[i] <= 127) {
            printf("%s%02x %s", GRN, file[i], WHT);
        }
        else {
            printf("%s%02x %s", BLU, file[i], WHT);
        }
        if ((i + 1) % 16 == 0) {
            printf(": %d\n", i / 16);
        }
    }

    const Elf64_Ehdr *eHdr = (Elf64_Ehdr *)file;

    printf("\ne_shoff %ld or 0x%08lx\n",eHdr->e_shoff, eHdr->e_shoff);

    printf("ndx = %d\n", eHdr->e_shstrndx);

    const Elf64_Shdr *shStrTab = (Elf64_Shdr *)&file[eHdr->e_shoff + (64 * eHdr->e_shstrndx)];
    (void)shStrTab;

    const char *shStrTab_data = (const char *)(file + shStrTab->sh_offset);


    int symtabNdx = find_symtab(file, eHdr, shStrTab_data);
    if (symtabNdx == -1) {
        ft_putstr_fd("Can't find .symtab in file", 2);
        munmap(file, file_size);
        exit(1);
    }
    printf("symtab ndx : %d\n", symtabNdx);

    print_all_symbols(file, eHdr, symtabNdx);

    munmap(file, file_size);
    return 0;
}

int main(int ac, char **av, char **env) {
    (void)env;

    if (ac == 1) {
        ft_nm("a.out");
    }
    else {
        for(int i = 1; av[i]; i++) {
            ft_nm(av[i]);
        }
    }

    return 0;
}