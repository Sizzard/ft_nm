/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:26:37 by facarval          #+#    #+#             */
/*   Updated: 2023/12/26 14:16:59 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == 0)
		return ((char *)(big));
	if (len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == 0)
				return ((char *)(&big[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}

/*

#include <bsd/string.h>

int	main(void)
{
	char	grand[30] = "aaabcabcd";
	char	petit[10] = "abcd";
	size_t	t;

	t = 9;
	printf("%s\n", ft_strnstr(grand, petit, t));
	printf("%s", strnstr(grand, petit, t));
}

*/