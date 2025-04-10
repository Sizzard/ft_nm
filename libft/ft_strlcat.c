/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:42:53 by facarval          #+#    #+#             */
/*   Updated: 2023/12/26 14:18:54 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	resultat;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	resultat = i + ft_strlen(src);
	while (j + i < size - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = 0;
	return (resultat);
}

/*

#include <bsd/string.h>

int	main(void)
{
	char	dest[] = "rrrrrrrrrrrrrrr";
	char	source[] = "lorem ipsum dolor sit amet";
	int		t;
	char	dest2[] = "rrrrrrrrrrrrrrr";
	char	source2[] = "lorem ipsum dolor sit amet";

	t = 5;
	printf("%zu : %s\n", ft_strlcat(dest, source, t), dest);
	printf("%zu : %s\n", strlcat(dest2, source2, t), dest2);
}

*/