/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:34:42 by facarval          #+#    #+#             */
/*   Updated: 2024/02/07 17:35:11 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, char c)
{
	int	i;
	int	compteur;

	i = 0;
	compteur = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			compteur++;
		i++;
	}
	return (compteur);
}

int	ft_len_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

char	**ft_error(const char *s, char **str, char c, int i)
{
	if (s[0] == '\0' && c == 0)
	{
		str = malloc(1 * sizeof(char *));
		str[0] = NULL;
		return (str);
	}
	while (i > 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split2(const char *s, char **str, char c, int *tab)
{
	while (tab[0] < ft_count_words(s, c))
	{
		while (s[tab[1]] == c && c != '\0')
			tab[1]++;
		tab[3] = tab[1];
		str[tab[0]] = malloc(ft_len_word(&s[tab[1]], c) + 1);
		if (!str[tab[0]])
			return (ft_error(s, str, c, tab[0]));
		while (tab[2] < ft_len_word(&s[tab[3]], c))
		{
			str[tab[0]][tab[2]] = s[tab[3] + tab[2]];
			tab[2]++;
		}
		str[tab[0]][tab[2]] = 0;
		tab[2] = 0;
		tab[0]++;
		tab[1] = tab[3] + ft_len_word(&s[tab[3]], c);
	}
	str[tab[0]] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		tab[4];
	char	**str;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	str = NULL;
	if (!s)
		return (NULL);
	if (s[0] == '\0' && c == 0)
		return (ft_error(s, str, c, tab[0]));
	str = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_split2(s, str, c, tab));
}

/*

void	print_str_array(char **str)
{
	while (*str)
	{
		printf("%s\n", *str);
		str++;
	}
}

int	main(void)
{
	const char	*input1 = 0;
	char		**result1;

	result1 = ft_split(input1, 0);
	printf("Résultat 1 : ");
	print_str_array(result1);
	return (0);
}

*/