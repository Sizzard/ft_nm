#include "../headers/ft_nm.h"

bool is_sorted_32(t_symbol_32 symbols[], int nb_entry) {
    for (int i = 1; i < nb_entry; i++) {
        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0)
            return false;
    }
    return true;
}

void sort_symbols_tab_32(t_symbol_32 symbols[], int nb_entry) {

    int i = 1;
    while (!is_sorted_32(symbols, nb_entry)) {
        if (i == nb_entry) {
            i = 1;
        }

        if (str_comp(symbols[i - 1].name, symbols[i].name) > 0) {
            t_symbol_32 tmp = symbols[i - 1];
            symbols[i - 1] = symbols[i];
            symbols[i] = tmp;
        }

        i++;
    }
}

bool is_reverse_sorted_32(t_symbol_32 symbols[], int nb_entry) {
    for (int i = 1; i < nb_entry; i++) {
        if (str_comp(symbols[i - 1].name, symbols[i].name) < 0)
            return false;
    }
    return true;
}

void reverse_sort_symbols_tab_32(t_symbol_32 symbols[], int nb_entry) {

    int i = 1;
    while (!is_reverse_sorted_32(symbols, nb_entry)) {
        if (i == nb_entry) {
            i = 1;
        }

        if (str_comp(symbols[i - 1].name, symbols[i].name) < 0) {
            t_symbol_32 tmp = symbols[i - 1];
            symbols[i - 1] = symbols[i];
            symbols[i] = tmp;
        }

        i++;
    }
}


int find_symtab_32(uint8_t *file, const Elf32_Ehdr *eHdr, const char *shStrTab_data) {
    int res = -1;
    for (int i = 0; i < eHdr->e_shnum; i++) {
        const long unsigned int sHdr_offset = eHdr->e_shoff + (sizeof(Elf32_Shdr) * i);
        if (sHdr_offset >= (long unsigned int)file_size) {
            return -1;
        }
        const Elf32_Shdr *sHdr = (Elf32_Shdr *)(file + sHdr_offset);
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

char get_symbol_letter_32(const uint8_t *file, const Elf32_Ehdr *eHdr ,const Elf32_Sym *sym) {
    if (ELF32_ST_BIND(sym->st_info) == STB_WEAK) {
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

    const Elf32_Shdr *sec = (Elf32_Shdr *)(file + eHdr->e_shoff + (sizeof(Elf32_Shdr) * sym->st_shndx));
    if (!is_within_file_range(file, (void *)sec)) {
            return '?';
    }
    if (sec->sh_type == SHT_NOBITS)
        return ELF32_ST_BIND(sym->st_info) == STB_LOCAL ? 'b' : 'B';
    if (sec->sh_flags & SHF_EXECINSTR) {
        return ELF32_ST_BIND(sym->st_info) == STB_LOCAL ? 't' : 'T';
    }
    if (sec->sh_flags & SHF_WRITE)
        return ELF32_ST_BIND(sym->st_info) == STB_LOCAL ? 'd' : 'D';
    if (!(sec->sh_flags & SHF_WRITE))
        return ELF32_ST_BIND(sym->st_info) == STB_LOCAL ? 'r' : 'R';

    return '?';
}

void print_value_32(const unsigned int value) {
    char buf[8];

    ft_memset(buf, '0', 8);

    int nb_len = get_number_len(value);

    write(1, buf, 8 - nb_len); 
    
    print_hexa(value, 1);
}

void print_symbol_32(const uint8_t *file, const Elf32_Ehdr *eHdr, const Elf32_Sym *sym, const t_symbol_32 symbol) {

    char letter = get_symbol_letter_32(file, eHdr, sym);

    uint8_t rendering = parse_letter(letter); 

    if (rendering == PRINT) {
        print_value_32(symbol.symTab->st_value);
        ft_printfd(1, " %c %s\n", letter, symbol.name);
    }
    else if (rendering == NO_VALUE) {
        ft_printfd(1, "         %c %s\n", letter, symbol.name);
    }
}

bool print_all_symbols_32(uint8_t *file, const Elf32_Ehdr *eHdr, int symtabNdx) {

    int symtab_offset = eHdr->e_shoff + (sizeof(Elf32_Shdr) * symtabNdx);
    if (symtab_offset >= file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }
    const Elf32_Shdr *symTab = (Elf32_Shdr *)(file + symtab_offset);
    if (!is_within_file_range(file, (void *)symTab)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    // print_sHdr(symTab);

    int strtab_section_offset = eHdr->e_shoff + symTab->sh_link * sizeof(Elf32_Shdr);
    if (strtab_section_offset >= file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }

    const Elf32_Shdr *strTab_section = (Elf32_Shdr *)(file + strtab_section_offset);
    if (strTab_section->sh_offset >= (long unsigned int)file_size) {
        ft_printfd(1, "File too short\n");
        return 1;
    }
    const char *strtab = (const char *)(file + strTab_section->sh_offset);

    t_symbol_32 *symbols = malloc(symTab->sh_size / symTab->sh_entsize * sizeof(t_symbol_32));
    if (!symbols) {
        ft_putstr_fd("Ran out of memory\n", 2);
        return 1;
    }

    // printf("%ld %ld\n", symTab->sh_size, sizeof(t_symbol_32));

    ft_memset(symbols, 0, symTab->sh_size / symTab->sh_entsize * sizeof(t_symbol_32));

    for (long unsigned int offset = 0, counter = 0; offset < symTab->sh_size; offset += 16, counter++) {
        const Elf32_Sym *effectiveSymTab = (Elf32_Sym *)(file + symTab->sh_offset + offset);
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
        // print_symbol_32(file, eHdr, effectiveSymTab, symbols[counter]);
        // print_sym(effectiveSymTab);
    }

    if (nm_args.p == false) {
        if (nm_args.r == false) {
            sort_symbols_tab_32(symbols, symTab->sh_size / symTab->sh_entsize);
        }
        else {
            reverse_sort_symbols_tab_32(symbols, symTab->sh_size / symTab->sh_entsize);
        }
    }

    for (int i = 0; i < (int)(symTab->sh_size / symTab->sh_entsize); i++) {
        if (symbols[i].name && symbols[i].name[0] != 0) {
            print_symbol_32(file, eHdr, symbols[i].symTab, symbols[i]);
        }
    }
    // printf("global %d, local %d, weak %d\n", STB_GLOBAL, STB_LOCAL, STB_WEAK);
    free(symbols);
    return 0;

}

bool handle_32_files(uint8_t *file) {
    const Elf32_Ehdr *eHdr = (Elf32_Ehdr *)file;
    if (!is_within_file_range(file, (void *)eHdr)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    // printf("\ne_shoff %ld or 0x%08lx\n",eHdr->e_shoff, eHdr->e_shoff);

    // printf("ndx = %d\n", eHdr->e_shstrndx);

    const Elf32_Shdr *shStrTab = (Elf32_Shdr *)&file[eHdr->e_shoff + (sizeof(Elf32_Shdr) * eHdr->e_shstrndx)];
    if (!is_within_file_range(file, (void *)shStrTab)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    const char *shStrTab_data = (const char *)(file + shStrTab->sh_offset);
    if (!is_within_file_range(file, (void *)shStrTab_data)) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }

    int symtabNdx = find_symtab_32(file, eHdr, shStrTab_data);
    if (symtabNdx == -1) {
        ft_putstr_fd("Error while parsing file\n", 2);
        return 1;
    }
    // printf("symtab ndx : %d\n", symtabNdx);

    return print_all_symbols_32(file, eHdr, symtabNdx);

}