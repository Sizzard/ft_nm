/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:47:49 by facarval          #+#    #+#             */
/*   Updated: 2024/02/09 11:02:00 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *line, int size)
{
	char	*temp;

	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	ft_strlcpy(temp, line, size);
	free(line);
	return (temp);
}

void	gnl3(char *stash, char *line, char *buffer, int *tab)
{
	while (tab[5] < tab[1])
	{
		line[tab[2]] = buffer[tab[5]];
		if (buffer[tab[5]] == '\n')
		{
			while (tab[5] + 1 < tab[1])
			{
				tab[5]++;
				stash[tab[3]] = buffer[tab[5]];
				tab[3]++;
			}
			stash[tab[3]] = 0;
			tab[4]++;
		}
		tab[5]++;
		tab[2]++;
	}
}
