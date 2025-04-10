/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:54:14 by facarval          #+#    #+#             */
/*   Updated: 2024/02/08 16:58:04 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_conversion
{
	int				compteur;
	unsigned long	hex_min;
	int				min;
	int				fd;
}					t_conversion;

int					ft_printfd(int fd, const char *s, ...);
int					ft_putstr_fd_compteur(char *s, int fd);
int					ft_putunbr_fd(unsigned int n, int fd, int *compteur);
int					ft_putnbr_fd_compteur(int n, int fd, int *compteur);
int					ft_putnbrbase(unsigned long nbr, int *compteur, int fd);
int					ft_putnbrbasemaj(unsigned int nbr, int *compteur, int fd);
int					ft_conversion(const char *s, int *j, va_list args,
						t_conversion uli);
void				ft_conversion2(const char *s, int *j, va_list args,
						t_conversion uli);
int					ft_putchar_fd(char c, int fd);

#endif