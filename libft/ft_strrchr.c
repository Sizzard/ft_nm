/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:05:36 by facarval          #+#    #+#             */
/*   Updated: 2023/11/09 14:50:30 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c;
	while (s[i])
		i++;
	while (i != -1)
	{
		if (s[i] == ch)
		{
			if (ch == 0)
				return ((char *)(&s[i]));
			return ((char *)(&s[i]));
		}
		i--;
	}
	return (NULL);
}

/*

int	main(void)
{
	printf("%s", ft_strrchr("tripouille", 't'));
	printf("\n%s", strrchr("tripouille", 't'));
}

*/