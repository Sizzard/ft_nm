#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_option {
    unsigned char opt;
    void *next;
} t_option; 

typedef struct s_argument {
    char *arg;
    void *next;
} t_argument; 

typedef struct s_argparse {
    t_option *options;
    t_argument *arguments;
} t_argparse;


void	    ft_lstadd_back_opt(t_option **lst, t_option *new);
void	    ft_lstclear_opt(t_option **lst);
t_option	*ft_lstnew_opt(unsigned char content);
void        print_lst_opt(t_option *opt);
bool        opt_contains(t_option *opt, const unsigned char contained);

void	    ft_lstadd_back_arg(t_argument **lst, t_argument *new);
void	    ft_lstclear_arg(t_argument **lst);
t_argument	*ft_lstnew_arg(char *content);
void        print_lst_arg(t_argument *arg);


t_argparse  *ft_argparse(int ac, char **av);
void        free_args(t_argparse *args);