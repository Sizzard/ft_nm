/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:23:23 by facarval          #+#    #+#             */
/*   Updated: 2023/12/26 14:29:38 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memmove2(size_t i, size_t n, char *str, const char *str2)
{
	i = n;
	while (i > 0)
	{
		i--;
		str[i] = str2[i];
	}
	return (str);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*str;
	const char	*str2;

	if (!dest || !src)
		return (NULL);
	i = 0;
	str = (char *)dest;
	str2 = (const char *)src;
	if (dest < src)
	{
		while (i < n)
		{
			str[i] = str2[i];
			i++;
		}
	}
	else
		ft_memmove2(i, n, str, str2);
	return (dest);
}

/**

int	main(void)
{
	size_t	t;
	char	dst[6] = "12345";
	char	source[6] = "00000";
	char	dst2[6] = "12345";
	char	source2[6] = "00000";

	t = 2;
	ft_memmove(dst, source, t);
	memmove(dst2, source2, t);
	printf("%s", dst);
	printf("\n%s", dst2);
}
*/