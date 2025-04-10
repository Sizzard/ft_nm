/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:56:25 by facarval          #+#    #+#             */
/*   Updated: 2023/11/17 11:23:33 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*first;
	t_list	*second_elem;

	if (!lst || !*f || !*del)
		return (NULL);
	dest = ft_lstnew((*f)(lst->content));
	if (!dest)
		return (NULL);
	first = dest;
	lst = lst->next;
	while (lst)
	{
		second_elem = ft_lstnew((*f)(lst->content));
		if (!second_elem)
			ft_lstclear(&first, del);
		ft_lstadd_back(&dest, second_elem);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (dest);
}
