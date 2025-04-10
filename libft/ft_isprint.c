/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:15:50 by facarval          #+#    #+#             */
/*   Updated: 2023/11/07 10:25:16 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*

#include <ctype.h>

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%d", ft_isprint(*argv[1]));
	printf("\n%d", isprint(*argv[1]));
}

*/