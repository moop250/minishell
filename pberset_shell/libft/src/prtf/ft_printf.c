/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:08 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 15:15:00 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_printf.h"

static int	flag_identifier(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 's')
		count += ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'i' || c == 'd')
		count += ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'u')
		count += ft_putuint_fd(va_arg(arg, unsigned int), 1);
	else if (c == 'x')
		count += ft_puthex_fd(va_arg(arg, unsigned int), 0, 1);
	else if (c == 'X')
		count += ft_puthex_fd(va_arg(arg, unsigned int), 1, 1);
	else if (c == 'p')
		count += ft_putptr_fd(va_arg(arg, void *), 1);
	else if (c == '%')
		count += ft_putchar_fd(c, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		chr_count;
	va_list	args;

	va_start(args, format);
	chr_count = 0;
	while (*format)
	{
		if (*format == '%' && ft_isprint(*(format + 1)))
		{
			chr_count += flag_identifier(*(format + 1), args);
			format++;
		}
		else
			chr_count += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (chr_count);
}
