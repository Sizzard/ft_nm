#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include <elf.h>
#include <stdbool.h>
#include <errno.h>
#include "../libft/libft.h"

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

enum {
    NO_PRINT,
    NO_VALUE,
    PRINT,
};


typedef struct s_symbol_32 {
    const Elf32_Sym     *symTab;
    char                *name;
} t_symbol_32;

typedef struct s_symbol_64 {
    const Elf64_Sym     *symTab;
    char                *name;
} t_symbol_64;

typedef struct s_nm_args {
    bool a;
    bool g;
    bool u;
    bool r;
    bool p;
    t_argparse *args;
} t_nm_args;

extern int  file_size;
extern t_nm_args nm_args;

int         get_file_size(int fd);

// void        print_file_content(uint8_t *file);
void        print_sym(const Elf64_Sym *symTab);

bool        init_nm_args(int ac, char **av);

bool        is_valid_elf_file(uint8_t *file);
void    	print_hexa(unsigned long nbr, int fd);
int         get_number_len(unsigned int nb);
int         str_comp(char *s1, char *s2);
void        print_value(const unsigned int value);
uint8_t     parse_letter(const unsigned char letter);
char        get_symbol_letter(const uint8_t *file, const Elf64_Ehdr *eHdr ,const Elf64_Sym *sym, const char *strtab);
void        print_symbol(const uint8_t *file, const Elf64_Ehdr *eHdr, const Elf64_Sym *sym, const t_symbol_64 symbol, const char *strtab);
bool        is_sorted(t_symbol_64 symbols[], int nb_entry);
void        sort_symbols_tab(t_symbol_64 symbols[], int nb_entry);

bool        is_sorted_32(t_symbol_32 symbols[], int nb_entry);
void        sort_symbols_tab_32(t_symbol_32 symbols[], int nb_entry);
int         find_symtab_32(uint8_t *file, const Elf32_Ehdr *eHdr, const char *shStrTab_data);
char        get_symbol_letter_32(const uint8_t *file, const Elf32_Ehdr *eHdr ,const Elf32_Sym *sym, const char *shStrTab_data);
void        print_symbol_32(const uint8_t *file, const Elf32_Ehdr *eHdr, const Elf32_Sym *sym, const t_symbol_32 symbol, const char *shStrTab_data);
bool        print_all_symbols_32(uint8_t *file, const Elf32_Ehdr *eHdr, int symtabNdx, const char *shStrTab_data);

bool        is_within_file_range(const uint8_t *file, void *ptr);

bool        handle_32_files(uint8_t *file);
bool        handle_64_files(uint8_t *file);

int         ft_nm(char *filepath);