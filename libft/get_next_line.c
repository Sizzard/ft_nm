/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:47:51 by facarval          #+#    #+#             */
/*   Updated: 2024/01/29 15:27:15 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 0 = fd
// 1 = br
// 2 = j pour line
// 3 = s pour stash
// 4 = n pour flag
// 5 = i pour buffer

char	*ft_clean(char *stash, char *line, int *tab)
{
	int	i;

	i = 0;
	while (stash[tab[3]] && stash[tab[3]] != '\n')
		line[tab[2]++] = stash[tab[3]++];
	if (stash[tab[3]] == '\n')
	{
		line[tab[2]] = '\n';
		line[tab[2] + 1] = 0;
		tab[3]++;
	}
	while (stash[tab[3]])
		stash[i++] = stash[tab[3]++];
	stash[i] = 0;
	tab[3] = 0;
	return (stash);
}

int	gnl2(char *stash, char **line, char *buffer, int *tab)
{
	while (tab[1] != 0 && tab[4] == 0)
	{
		tab[6]++;
		tab[1] = read(tab[0], buffer, BUFFER_SIZE);
		*line = ft_realloc(*line, tab[6] * BUFFER_SIZE + 1);
		if (*line == NULL)
			return (1);
		gnl3(stash, *line, buffer, tab);
		tab[5] = 0;
	}
	(*line)[tab[2]] = 0;
	free(buffer);
	return (0);
}

int	ft_check_malloc(char *stash, char **line, char *buffer, int *tab)
{
	if (BUFFER_SIZE <= 0 || tab[0] < 0 || read(tab[0], &buffer, 0) < 0)
		return (1);
	*line = malloc(BUFFER_SIZE + 1);
	if (*line == NULL)
		return (1);
	ft_bzero(*line, BUFFER_SIZE + 1);
	ft_clean(stash, *line, tab);
	return (0);
}

void	ft_tab_init(int *tab, int fd)
{
	tab[0] = fd;
	tab[1] = 1;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
	tab[6] = 1;
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	static int	compteur;
	char		*line;
	char		*buffer;
	int			tab[7];

	ft_tab_init(tab, fd);
	line = 0;
	buffer = 0;
	compteur += 1;
	if (ft_check_malloc(stash, &line, buffer, tab) == 1)
		return (NULL);
	if (compteur != 1 && line[tab[2]] == '\n')
		return (line);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	if (gnl2(stash, &line, buffer, tab))
		return (NULL);
	if (line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*ligne;
// 	int		i;

// 	i = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		ligne = get_next_line(fd);
// 		if (ligne == NULL)
// 		{
// 			printf("%s", ligne);
// 			break ;
// 		}
// 		printf("%d: %s", i, ligne);
// 		free(ligne);
// 		i++;
// 	}
// 	return (0);
// }
