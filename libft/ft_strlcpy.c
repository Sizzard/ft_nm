/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:14:12 by facarval          #+#    #+#             */
/*   Updated: 2023/11/14 10:56:44 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)

{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	while (src[j])
		j++;
	return (j);
}

/*

#include <bsd/string.h>

int	main(void)
{
	size_t		p;
	char		dest[] = "";
	const char	source[] = "123";
	char		destt[] = "";
	const char	sourcee[] = "123";

	p = -5;
	printf("%zu %s\n", ft_strlcpy(dest, source, p), dest);
	printf("%zu %s", strlcpy(destt, sourcee, p), destt);
}
*/