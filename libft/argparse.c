#include "argparse.h"

t_option *parse_option(t_option *opt, char *str) {

    t_option *res = opt;

    for (size_t i = 1; str[i]; i++) {
        if (opt_contains(res, str[i])) {
            continue;
        }
        t_option *new_node = ft_lstnew_opt(str[i]);
        if (!new_node) {
            return NULL;
        }
        ft_lstadd_back_opt(&res, new_node);
    }
    return res;
}

t_argparse *ft_argparse(int ac, char **av) {
    t_argparse *res = NULL;
    t_option *opt = NULL;
    t_argument *arg = NULL;

    (void)ac;
    res = malloc(sizeof(t_argparse));
    if (!res) {
        return NULL;
    }

    
    for(size_t i = 1; av[i]; i++) {
        if (av[i][0] == '-' && av[i][1] != 0) {
            t_option *new_node = parse_option(opt, av[i]);
            if (!new_node) {
                ft_lstclear_opt(&opt);
                ft_lstclear_arg(&arg);
                return NULL;
            }
            if (new_node != opt) {
                ft_lstadd_back_opt(&opt, new_node);
            }
        }
        else {
            t_argument *new_node = ft_lstnew_arg(av[i]);
            if (new_node == NULL) {
                ft_lstclear_opt(&opt);
                ft_lstclear_arg(&arg);
                return NULL;
            }
            ft_lstadd_back_arg(&arg, new_node);
        }
    }

    res->options = opt;
    res->arguments = arg;
    // print_lst_opt(opt);
    // print_lst_arg(arg);
    return res;
}

void free_args(t_argparse *args) {
    if (args) {
        ft_lstclear_opt(&args->options);
        ft_lstclear_arg(&args->arguments);
        free(args);
    }
}

// int main(int ac, char **av) {
//     t_argparse *args = ft_argparse(ac,av);
//     free_args(args);

// }