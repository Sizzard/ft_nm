/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:01:04 by facarval          #+#    #+#             */
/*   Updated: 2024/03/29 10:27:46 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) {
        // printf("%u\n", *s1);
        s1++;
        s2++;
    }
    return *s1 - *s2;
}



// int	main(void)
// {

//     char *s1 = "";
//     char *s2 = "";
// 	printf("Ma fonction : %d\n", ft_strcmp(s1, s2));
// 	printf("Vraie Fonction : %d", strcmp(s1, s2));
// }