#include "../headers/ft_nm.h"

bool is_sorted(t_symbol_64 symbols[], int nb_entry) {
    for (int i = 1; i < nb_entry; i++) {
        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0)
            return false;
    }
    return true;
}

void sort_symbols_tab(t_symbol_64 symbols[], int nb_entry) {

    int i = 1;
    while (!is_sorted(symbols, nb_entry)) {
        if (i == nb_entry) {
            i = 1;
        }

        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0) {
            t_symbol_64 tmp = symbols[i - 1];
            symbols[i - 1] = symbols[i];
            symbols[i] = tmp;
        }

        i++;
    }
}

bool is_reverse_sorted(t_symbol_64 symbols[], int nb_entry) {
    for (int i = 1; i < nb_entry; i++) {
        if (str_comp(symbols[i - 1].name, symbols[i].name) < 0)
            return false;
    }
    return true;
}

void reverse_sort_symbols_tab(t_symbol_64 symbols[], int nb_entry) {

    int i = 1;
    while (!is_reverse_sorted(symbols, nb_entry)) {
        if (i == nb_entry) {
            i = 1;
        }

        if (str_comp(symbols[i - 1].name, symbols[i].name) < 0) {
            t_symbol_64 tmp = symbols[i - 1];
            symbols[i - 1] = symbols[i];
            symbols[i] = tmp;
        }

        i++;
    }
}


int find_symtab(uint8_t *file, const Elf64_Ehdr *eHdr, const char *shStrTab_data) {
    int res = -1;
    for (int i = 0; i < eHdr->e_shnum; i++) {
        const long unsigned int sHdr_offset = eHdr->e_shoff + (sizeof(Elf64_Shdr) * i);
        if (sHdr_offset >= (long unsigned int)file_size) {
            return -1;
        }
        const Elf64_Shdr *sHdr = (Elf64_Shdr *)(file + sHdr_offset);
        if (!is_within_file_range(file, (void *)sHdr)) {
            return -1;
        }
        const char *section_name = shStrTab_data + sHdr->sh_name;
        if (!is_within_file_range(file, (void *)section_name)) {
            return -1;
        }
        // printf(" [%2d] : %s\n", i, section_name);
        if (ft_strncmp(section_name, ".symtab", ft_strlen(".symtab")) == 0) {
            // printf("%s found at index %d\n", section_name, i);
            res = i;
        }
    }
    return res;
}

char get_symbol_letter(const uint8_t *file, const Elf64_Ehdr *eHdr ,const Elf64_Sym *sym, const char *shStrTab_data) {
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (sym->st_shndx == SHN_UNDEF)
            return 'w';
        else
            return 'W';
    }

    if (sym->st_shndx == SHN_ABS) {
        return 'a';
    }
    if (sym->st_shndx == SHN_UNDEF) {
        return 'U';
    }
    if (sym->st_shndx == SHN_COMMON)
        return 'C';

    const Elf64_Shdr *sec = (Elf64_Shdr *)(file + eHdr->e_shoff + (sizeof(Elf64_Shdr) * sym->st_shndx));
    const char *name = shStrTab_data + sec->sh_name;

    if (!is_within_file_range(file, (void *)sec)) {
            return '?';
    }

    if (sec->sh_type == 17 && name && (ft_strcmp(name, ".debug") == 0 || ft_strcmp(name, ".group") == 0)) {
        return 'n';
    }
    
    if (sec->sh_type == SHT_NOBITS)
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'b' : 'B';
    if (sec->sh_flags & SHF_EXECINSTR) {
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 't' : 'T';
    }
    if (sec->sh_flags & SHF_WRITE)
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'd' : 'D';
    if (!(sec->sh_flags & SHF_WRITE))
        return ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'r' : 'R';

    return '?';
}


void print_symbol(const uint8_t *file, const Elf64_Ehdr *eHdr, const Elf64_Sym *sym, const t_symbol_64 symbol, const char *shStrTab_data) {

    char letter = get_symbol_letter(file, eHdr, sym, shStrTab_data);

    uint8_t rendering = parse_letter(letter); 

    if (rendering == PRINT) {
        print_value(symbol.symTab->st_value);
        ft_printfd(1, " %c %s\n", letter, symbol.name);
    }
    else if (rendering == NO_VALUE) {
        ft_printfd(1, "                 %c %s\n", letter, symbol.name);
    }
}

bool print_all_symbols(uint8_t *file, const Elf64_Ehdr *eHdr, int symtabNdx, const char *shStrTab_data) {

    int symtab_offset = eHdr->e_shoff + (sizeof(Elf64_Shdr) * symtabNdx);
    if (symtab_offset >= file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }
    const Elf64_Shdr *symTab = (Elf64_Shdr *)(file + symtab_offset);
    if (!is_within_file_range(file, (void *)symTab)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    // print_sHdr(symTab);

    int strtab_section_offset = eHdr->e_shoff + symTab->sh_link * sizeof(Elf64_Shdr);
    if (strtab_section_offset >= file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }

    const Elf64_Shdr *strTab_section = (Elf64_Shdr *)(file + strtab_section_offset);
    if (strTab_section->sh_offset >= (long unsigned int)file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }
    const char *strtab = (const char *)(file + strTab_section->sh_offset);

    t_symbol_64 *symbols = malloc(symTab->sh_size / symTab->sh_entsize * sizeof(t_symbol_64));
    if (!symbols) {
        ft_putstr_fd("Ran out of memory\n", 2);
        return 1;
    }

    // printf("%ld %ld\n", symTab->sh_size, sizeof(t_symbol_64));

    ft_memset(symbols, 0, symTab->sh_size / symTab->sh_entsize * sizeof(t_symbol_64));

    for (long unsigned int offset = 0, counter = 0; offset < symTab->sh_size; offset += 24, counter++) {
        const Elf64_Sym *effectiveSymTab = (Elf64_Sym *)(file + symTab->sh_offset + offset);
        if (!is_within_file_range(file, (void *)effectiveSymTab)) {
            ft_putstr_fd("Error while parsing file\n", 2);
            free(symbols);
            return 1;
        }
        const char *name = strtab + effectiveSymTab->st_name;
        if (!is_within_file_range(file, (void *)name)) {
            ft_putstr_fd("Error while parsing file\n", 2);
            free(symbols);
            return 1;
        }
        symbols[counter].name = (char *)name;
        symbols[counter].symTab = effectiveSymTab;
        // print_symbol(file, eHdr, effectiveSymTab, symbols[counter]);
        // print_sym(effectiveSymTab);
    }

    if (nm_args.p == false) {
        if (nm_args.r == false) {
            sort_symbols_tab(symbols, symTab->sh_size / symTab->sh_entsize);
        }
        else {
            reverse_sort_symbols_tab(symbols, symTab->sh_size / symTab->sh_entsize);
        }
    }

    for (int i = 0; i < (int)(symTab->sh_size / symTab->sh_entsize); i++) {
        if (symbols[i].name && symbols[i].name[0] != 0) {
            print_symbol(file, eHdr, symbols[i].symTab, symbols[i], shStrTab_data);
        }
    }
    // printf("global %d, local %d, weak %d\n", STB_GLOBAL, STB_LOCAL, STB_WEAK);
    free(symbols);
    return 0;

}

bool handle_64_files(uint8_t *file) {
    const Elf64_Ehdr *eHdr = (Elf64_Ehdr *)file;
    if (!is_within_file_range(file, (void *)eHdr)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    // printf("\ne_shoff %ld or 0x%08lx\n",eHdr->e_shoff, eHdr->e_shoff);

    // printf("ndx = %d\n", eHdr->e_shstrndx);

    const Elf64_Shdr *shStrTab = (Elf64_Shdr *)&file[eHdr->e_shoff + (sizeof(Elf64_Shdr) * eHdr->e_shstrndx)];
    if (!is_within_file_range(file, (void *)shStrTab)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    const char *shStrTab_data = (const char *)(file + shStrTab->sh_offset);
    if (!is_within_file_range(file, (void *)shStrTab_data)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    int symtabNdx = find_symtab(file, eHdr, shStrTab_data);
    if (symtabNdx == -1) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }
    // printf("symtab ndx : %d\n", symtabNdx);

    return print_all_symbols(file, eHdr, symtabNdx, shStrTab_data);

}