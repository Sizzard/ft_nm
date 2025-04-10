/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:45:22 by facarval          #+#    #+#             */
/*   Updated: 2024/02/09 10:56:52 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*ft_realloc(char *line, int size);
void	gnl3(char *stash, char *line, char *buffer, int *tab);
char	*ft_clean(char *stash, char *line, int *tab);
int		gnl2(char *stash, char **line, char *buffer, int *tab);
int		ft_check_malloc(char *stash, char **line, char *buffer, int *tab);
void	ft_tab_init(int *tab, int fd);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000

# endif
#endif