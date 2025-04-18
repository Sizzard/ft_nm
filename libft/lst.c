#include "argparse.h"

size_t ft_lst_strlen(char *str) {
    size_t i = 0;
    while ( str[i]) {
        i++;
    }
    return i;
}

void	ft_lstadd_back_opt(t_option **lst, t_option *new)
{
	t_option	*list;
	t_option	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	last = 0;
	while (list != NULL)
	{
		last = list;
		list = list->next;
	}
	last->next = new;
}

void	ft_lstclear_opt(t_option **lst)
{
	t_option	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}

t_option	*ft_lstnew_opt(unsigned char content)
{
	t_option	*lst;

	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->opt = content;
	lst->next = NULL;
	return (lst);
}

bool opt_contains(t_option *opt, const unsigned char contained) {
    for (; opt; opt= opt->next) {
        if (opt->opt == contained) {
            return true;
        }
    }
    return false;
}

void print_lst_opt(t_option *opt) {
    for (; opt; opt = opt->next) {
		unsigned char buf[2];
		buf[0] = opt->opt;
		buf[1] = '\n';
		write(1, buf, 2);
    }
    
}

void	ft_lstadd_back_arg(t_argument **lst, t_argument *new)
{
	t_argument	*list;
	t_argument	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	last = 0;
	while (list != NULL)
	{
		last = list;
		list = list->next;
	}
	last->next = new;
}

void	ft_lstclear_arg(t_argument **lst)
{
	t_argument	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}

t_argument	*ft_lstnew_arg(char *content)
{
	t_argument	*lst;

	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->arg = content;
	lst->next = NULL;
	return (lst);
}

void print_lst_arg(t_argument *arg) {
    for (t_argument *tmp = arg; tmp; tmp = tmp->next) {
    	write(1, tmp->arg, ft_lst_strlen(tmp->arg));
		write(1, "\n", 1);
    }
    
}