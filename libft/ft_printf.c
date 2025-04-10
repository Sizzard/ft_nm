/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facarval <facarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:04:34 by facarval          #+#    #+#             */
/*   Updated: 2023/12/06 12:16:00 by facarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversion(const char *s, int *j, va_list args)
{
	t_conversion	uli;

	uli.compteur = 0;
	j[0]++;
	if ((s[j[0]] == 'd') || s[j[0]] == 'i')
	{
		uli.min = va_arg(args, int);
		ft_putnbr_fd_compteur(uli.min, 1, &uli.compteur);
		if (uli.min == -2147483648)
			uli.compteur += 10;
		if (uli.min < 0)
			uli.compteur++;
	}
	else if (s[j[0]] == 's')
		uli.compteur = ft_putstr_fd_compteur(va_arg(args, char *), 1);
	else if (s[j[0]] == 'c')
		uli.compteur = ft_putchar_fd(va_arg(args, int), 1);
	else if (s[j[0]] == 'u')
		ft_putunbr_fd(va_arg(args, unsigned int), 1, &uli.compteur);
	ft_conversion2(s, j, args, uli);
	return (j[1] += uli.compteur);
}

void	ft_conversion2(const char *s, int *j, va_list args, t_conversion uli)
{
	if (s[j[0]] == 'x')
		j[1] += ft_putnbrbase(va_arg(args, unsigned int), &uli.compteur);
	else if (s[j[0]] == 'X')
		j[1] += ft_putnbrbasemaj(va_arg(args, unsigned int), &uli.compteur);
	else if (s[j[0]] == 'p')
	{
		uli.hex_min = va_arg(args, unsigned long);
		if (!uli.hex_min)
		{
			j[1] += write(1, "(nil)", 5);
			return ;
		}
		j[1] += write(1, "0x", 2);
		j[1] += ft_putnbrbase(uli.hex_min, &uli.compteur);
	}
}

void	ft_printf2(const char *s, int *j, va_list args)
{
	while (s[j[0]])
	{
		if (s[j[0]] != '%')
			ft_putchar_fd(s[j[0]], 1);
		if (s[j[0]] == '%' && s[j[0] + 1] == '%')
		{
			ft_putchar_fd('%', 1);
			j[0]++;
		}
		else if (s[j[0]] == '%')
		{
			ft_conversion(s, j, args);
			j[1]--;
		}
		j[1]++;
		j[0]++;
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		j[2];

	j[0] = 0;
	j[1] = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	ft_printf2(s, j, args);
	va_end(args);
	return (j[1]);
}

/*

int	main(void)
{
	char	*test;

	test = "848";
	printf("%d", ft_printf("%s", NULL));
	printf("\n");
	printf("%d", printf("%s", NULL));
	return (0);
}
*/