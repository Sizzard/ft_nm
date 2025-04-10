/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:50:56 by facarval          #+#    #+#             */
/*   Updated: 2024/02/09 12:36:58 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	if (!s1 || !s2)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		i++;
	res = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (res);
}

// int	main(void)
// {
// 	size_t		t;
// 	const char	*str1 = NULL;
// 	const char	str2[] = "1234Z";

// 	t = 50;
// 	printf("%d\n", ft_strncmp(str1, str2, t));
// 	printf("%d", strncmp(str1, str2, t));
// }
