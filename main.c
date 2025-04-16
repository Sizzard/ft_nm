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
    int res = -1;
    for (int i = 0; i < eHdr->e_shnum; i++) {
        const Elf64_Shdr *sHdr = (Elf64_Shdr *)(file + eHdr->e_shoff + (64 * i));
        const char *section_name = shStrTab_data + sHdr->sh_name;
        printf(" [%2d] : %s\n", i, section_name);
        if (ft_strncmp(section_name, ".symtab", ft_strlen(".symtab")) == 0) {
            printf("%s found at index %d\n", section_name, i);
            res = i;
        }
    }
    return res;
}

void print_sHdr(const Elf64_Shdr *sHdr) {
    ft_putstr_fd("sHdr entry : \n", 1);
    printf("sh_name : %d or 0x%08x\n", sHdr->sh_name, sHdr->sh_name);
    printf("sh_type : %d or 0x%08x\n", sHdr->sh_type, sHdr->sh_type);
    printf("sh_flags : %ld or 0x%08lx\n", sHdr->sh_flags, sHdr->sh_flags);
    printf("sh_addr : %ld or 0x%08lx\n", sHdr->sh_addr, sHdr->sh_addr);
    printf("sh_offset : %ld or 0x%08lx\n", sHdr->sh_offset, sHdr->sh_offset);
    printf("sh_size : %ld or 0x%08lx\n", sHdr->sh_size, sHdr->sh_size);
    printf("sh_link : %d or 0x%08x\n", sHdr->sh_link, sHdr->sh_link);
    printf("sh_info : %d or 0x%08x\n", sHdr->sh_info, sHdr->sh_info);
    printf("sh_addralign : %ld or 0x%08lx\n", sHdr->sh_addralign, sHdr->sh_addralign);
    printf("sh_entsize : %ld or 0x%08lx\n", sHdr->sh_entsize, sHdr->sh_entsize);
    printf("Number of entries of the symbol table : %ld\n", sHdr->sh_size / sHdr->sh_entsize);
}

void print_sym(const Elf64_Sym *symTab) {
    printf("st_name : %d or 0x%08x\n", symTab->st_name, symTab->st_name);
    printf("st_info : %d or 0x%08x\n", symTab->st_info, symTab->st_info);
    printf("st_other : %d or 0x%08x\n", symTab->st_other, symTab->st_other);
    printf("st_shndx : %d or 0x%08x\n", symTab->st_shndx, symTab->st_shndx);
    printf("st_value : %ld or 0x%08lx\n", symTab->st_value, symTab->st_value);
    printf("st_size : %ld or 0x%08lx\n", symTab->st_size, symTab->st_size);
}

char get_symbol_letter(const uint8_t *file, const Elf64_Ehdr *eHdr ,const Elf64_Sym *sym) {
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (sym->st_shndx == SHN_UNDEF)
            return 'w';
        else
            return 'W';
    }

    if (sym->st_shndx == SHN_UNDEF)
        return 'U';
    if (sym->st_shndx == SHN_ABS)
        return 'A';
    if (sym->st_shndx == SHN_COMMON)
        return 'C';

    const Elf64_Shdr *sec = (Elf64_Shdr *)(file + eHdr->e_shoff + (sizeof(Elf64_Shdr) * sym->st_shndx));
    if (sec->sh_type == SHT_NOBITS)
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'b' : 'B';
    if (sec->sh_flags & SHF_EXECINSTR)
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 't' : 'T';
    if (sec->sh_flags & SHF_WRITE)
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'd' : 'D';
    if (!(sec->sh_flags & SHF_WRITE))
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'r' : 'R';

    return '?';
}

void print_symbol(const uint8_t *file, const Elf64_Ehdr *eHdr, const Elf64_Sym *sym, const t_symbol symbol) {

    char letter = get_symbol_letter(file, eHdr, sym);
    if (letter != 'A' && letter != 'U') {
        printf("%016lx %c %s\n", symbol.symTab->st_value, letter, symbol.name);
    }
    else if (letter == 'U') {
        printf("                 %c %s\n", letter, symbol.name);
    }
}

int str_comp(char *s1, char *s2) {
    int i = 0, j = 0;

    if (!s1 || !s2)
        return 0;

    while (s1[i] == '_') i++;
    while (s2[j] == '_') j++;

    while (s1[i] && s2[j]) {

        char c1 = ft_tolower((unsigned char)s1[i]);
        char c2 = ft_tolower((unsigned char)s2[j]);

        if (c1 != c2)
            return c1 - c2;

        i++;
        j++;
    }

    return ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[j]);
}

bool is_sorted(t_symbol symbols[], int nb_entry) {
    for (int i = 1; i < nb_entry; i++) {
        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0)
            return false;
    }
    return true;
}

void sort_symbols_tab(t_symbol symbols[], int nb_entry) {

    int i = 1;
    while (!is_sorted(symbols, nb_entry)) {
        if (i == nb_entry) {
            i = 1;
        }

        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0) {
            t_symbol tmp = symbols[i - 1];
            symbols[i - 1] = symbols[i];
            symbols[i] = tmp;
        }

        i++;
    }
}


void print_all_symbols(uint8_t *file, const Elf64_Ehdr *eHdr, int symtabNdx) {

    const Elf64_Shdr *symTab = (Elf64_Shdr *)(file + eHdr->e_shoff + (64 * symtabNdx));

    print_sHdr(symTab);

    const Elf64_Shdr *strTab_section = (Elf64_Shdr *)(file + eHdr->e_shoff + symTab->sh_link * sizeof(Elf64_Shdr));
    const char *strtab = (const char *)(file + strTab_section->sh_offset);
    (void)strtab;

    t_symbol symbols[4096];

    printf("%ld %ld\n", symTab->sh_size, sizeof(t_symbol));

    ft_memset(symbols, 0, 4096 * sizeof(t_symbol));

    for (long unsigned int offset = 0, counter = 0; offset < symTab->sh_size; offset += 24, counter++) {
        const Elf64_Sym *effectiveSymTab = (Elf64_Sym *)(file + symTab->sh_offset + offset);
        const char *name = strtab + effectiveSymTab->st_name;
        ft_strlcpy(symbols[counter].name, name, ft_strlen(name) + 1);
        symbols[counter].symTab = effectiveSymTab;
        // print_symbol(file, eHdr, effectiveSymTab, symbols[counter]);
        // print_sym(effectiveSymTab);
    }

    sort_symbols_tab(symbols, symTab->sh_size / symTab->sh_entsize);

    for (int i = 0; i < 4096; i++) {
        if (symbols[i].name[0] != 0) {
            print_symbol(file, eHdr, symbols[i].symTab, symbols[i]);
        }
    }
    // printf("global %d, local %d, weak %d\n", STB_GLOBAL, STB_LOCAL, STB_WEAK);

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
            printf(": %d\n", i / 16 + 1);
        }
    }

    const Elf64_Ehdr *eHdr = (Elf64_Ehdr *)file;

    printf("\ne_shoff %ld or 0x%08lx\n",eHdr->e_shoff, eHdr->e_shoff);

    printf("ndx = %d\n", eHdr->e_shstrndx);

    const Elf64_Shdr *shStrTab = (Elf64_Shdr *)&file[eHdr->e_shoff + (sizeof(Elf64_Shdr) * eHdr->e_shstrndx)];

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