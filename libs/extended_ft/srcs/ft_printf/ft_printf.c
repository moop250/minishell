/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:03:15 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 13:53:45 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_printf_putnbrun(unsigned long int n, char *str, int *p, int fd)
{
	unsigned int	i;

	i = ft_strlen(str);
	if (n >= i)
	{
		ft_printf_putnbrun(n / i, str, p, fd);
		ft_printf_putnbrun(n % i, str, p, fd);
	}
	else
		ft_printf_putchar(str[n], p, fd);
}

static void	ft_printf_format(char in, va_list args, int *p, int fd)
{
	if (in == 0)
		ft_printf_putstr("(null)", p, fd);
	else if (in == 'c')
		ft_printf_putchar((char)va_arg(args, int), p, fd);
	else if (in == 's')
		ft_printf_putstr(va_arg(args, char *), p, fd);
	else if (in == 'p')
		ft_printf_ptohex(va_arg(args, void *), p, fd);
	else if (in == 'd' || in == 'i')
		ft_printf_putnbr(va_arg(args, int), "0123456789", p, fd);
	else if (in == 'u')
		ft_printf_putnbrun(va_arg(args, unsigned int), "0123456789", p, fd);
	else if (in == 'x')
		ft_printf_putnbr(va_arg(args, int), "0123456789abcdef", p, fd);
	else if (in == 'X')
		ft_printf_putnbr(va_arg(args, int), "0123456789ABCDEF", p, fd);
	else if (in == '%')
		ft_printf_putchar('%', p, fd);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		a;
	int		*p;
	va_list	args;

	i = 0;
	a = 0;
	p = &a;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_printf_format(format[i++], args, p, fd);
		}
		else
			ft_printf_putchar(format[i++], p, fd);
	}
	va_end(args);
	return (a);
}
