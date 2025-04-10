/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:12:33 by facarval          #+#    #+#             */
/*   Updated: 2023/12/26 14:34:43 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	is_char(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	is_delim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = 0;
	l = 0;
	while (is_char(s1[i], set) == 1)
	{
		j++;
		i++;
	}
	while (s1[i + 1])
		i++;
	while (is_char(s1[i], set) == 1)
	{
		j++;
		i--;
	}
	while (s1[l])
		l++;
	return (l - j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (ft_strdup(""));
	str = malloc(is_delim(s1, set) + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	while (is_char(s1[i], set) == 1)
		i++;
	while (j != is_delim(s1, set))
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}

/*

int	main(void)
{
	char	tab1[] = "abc123abc456abc789abc";
	char	tab2[] = "acb";

	printf("%s", ft_strtrim(tab1, tab2));
}

*/