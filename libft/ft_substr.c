/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:27:30 by facarval          #+#    #+#             */
/*   Updated: 2023/11/13 14:32:53 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_taille(char const *tab, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (tab[start])
	{
		start++;
		i++;
	}
	if (len > i)
		return (i);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(ft_taille(s, start, len) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

/*

int	main(int argc, char **argv)
{
	char	phrase[] = "Ceci est un test !";

	(void)argc;
	printf("%s", ft_substr(phrase, atoi(&argv[1][0]), atoi(&argv[2][0])));
}

*/