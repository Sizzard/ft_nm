/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:47:25 by facarval          #+#    #+#             */
/*   Updated: 2023/11/06 17:02:06 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*

#include <ctype.h>

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%d", ft_isdigit(*argv[1]));
	printf("\n%d", isdigit(*argv[1]));
	return (0);
}

*/