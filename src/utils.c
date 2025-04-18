#include "../headers/ft_nm.h"

int get_file_size(int fd) {
    struct stat st;
    if (fstat(fd, &st) == -1) {
        return -1;
    }
    return st.st_size;
}

bool is_valid_elf_file(uint8_t *file) {
    uint32_t magic_number = 0;
    ft_memcpy(&magic_number, file, 4);
    if (magic_number != 0x464c457f) {
        return false;
    }
    return true;
}

// void print_file_content(uint8_t *file) {
//     for(int i = 0; i < file_size; i++) {
//         if (file[i] == 0) {
//             printf("%s%02X %s", BLK, file[i], WHT);
//         }
//         else if (file[i] <= 127) {
//             printf("%s%02x %s", GRN, file[i], WHT);
//         }
//         else {
//             printf("%s%02x %s", BLU, file[i], WHT);
//         }
//         if ((i + 1) % 16 == 0) {
//             printf(": %d\n", i / 16 + 1);
//         }
//     }
//     printf("\n");
// }

// void print_sHdr(const Elf64_Shdr *sHdr) {
//     ft_putstr_fd("sHdr entry : \n", 1);
//     printf("sh_name : %d or 0x%08x\n", sHdr->sh_name, sHdr->sh_name);
//     printf("sh_type : %d or 0x%08x\n", sHdr->sh_type, sHdr->sh_type);
//     printf("sh_flags : %ld or 0x%08lx\n", sHdr->sh_flags, sHdr->sh_flags);
//     printf("sh_addr : %ld or 0x%08lx\n", sHdr->sh_addr, sHdr->sh_addr);
//     printf("sh_offset : %ld or 0x%08lx\n", sHdr->sh_offset, sHdr->sh_offset);
//     printf("sh_size : %ld or 0x%08lx\n", sHdr->sh_size, sHdr->sh_size);
//     printf("sh_link : %d or 0x%08x\n", sHdr->sh_link, sHdr->sh_link);
//     printf("sh_info : %d or 0x%08x\n", sHdr->sh_info, sHdr->sh_info);
//     printf("sh_addralign : %ld or 0x%08lx\n", sHdr->sh_addralign, sHdr->sh_addralign);
//     printf("sh_entsize : %ld or 0x%08lx\n", sHdr->sh_entsize, sHdr->sh_entsize);
//     printf("Number of entries of the symbol table : %ld\n", sHdr->sh_size / sHdr->sh_entsize);
// }

// void print_sym(const Elf64_Sym *symTab) {
//     printf("st_name : %d or 0x%08x\n", symTab->st_name, symTab->st_name);
//     printf("st_info : %d or 0x%08x\n", symTab->st_info, symTab->st_info);
//     printf("st_other : %d or 0x%08x\n", symTab->st_other, symTab->st_other);
//     printf("st_shndx : %d or 0x%08x\n", symTab->st_shndx, symTab->st_shndx);
//     printf("st_value : %ld or 0x%08lx\n", symTab->st_value, symTab->st_value);
//     printf("st_size : %ld or 0x%08lx\n", symTab->st_size, symTab->st_size);
// }

void	print_hexa(unsigned long nbr, int fd)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr >= 16)
		print_hexa(nbr / 16, fd);
	ft_putchar_fd(base[nbr % 16], fd);
}

int get_number_len(unsigned int nb) {
    int i = 1;

    while (nb >= 16) {
        nb = nb /16;
        i++;
    }
    return i;
}

void print_value(const unsigned int value) {
    char buf[16];

    ft_memset(buf, '0', 16);

    int nb_len = get_number_len(value);

    write(1, buf, 16 - nb_len); 
    
    print_hexa(value, 1);
}

uint8_t parse_letter(const unsigned char letter) {
    if (letter == 'A') {
        return NO_PRINT;
    }
    else if (letter == 'U' || letter == 'w') {
        return NO_VALUE;
    }
    return PRINT;
}


int str_comp(char *s1, char *s2) {
    int i = 0, j = 0;

    if (!s1 || !s2)
        return 0;


    while (s1[i] && s2[j]) {

        while (!ft_isalpha(s1[i])) i++;
        while (!ft_isalpha(s2[j])) j++;

        char c1 = ft_tolower((unsigned char)s1[i]);
        char c2 = ft_tolower((unsigned char)s2[j]);

        if (c1 != c2)
            return c1 - c2;

        i++;
        j++;
    }
    if (ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[j]) == 0 && i < j) {
        return 1;
    }
    else if (ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[j]) == 0 && i > j) {
        return -1;
    }
    return ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[j]);
}

bool is_within_file_range(const uint8_t *file, void *ptr) {
    if ( (uintptr_t)ptr >= (uintptr_t)file && (uintptr_t)ptr < (uintptr_t)(file + file_size)) {
        return true;
    }
    return false;
}