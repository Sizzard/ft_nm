/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:49:23 by facarval          #+#    #+#             */
/*   Updated: 2023/12/18 16:22:17 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int			l;
	int			min;
	long int	nbr;

	min = 0;
	nbr = n;
	l = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		min -= 1;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		l++;
	}
	if (min == -1)
		return (l + 1);
	return (l);
}

char	*ft_itoa2(long int n, char *str)
{
	if (n > 9)
		str = ft_itoa2(n / 10, str);
	*str = n % 10 + '0';
	return (str + 1);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	char		*str;

	nbr = (long int)n;
	str = malloc(ft_len(n) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		ft_itoa2(-nbr, &str[1]);
	}
	else
		ft_itoa2(nbr, str);
	str[ft_len(n)] = 0;
	return (str);
}

/*

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s", ft_itoa(atoi(&argv[1][0])));
}
*/