/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:45:50 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/20 14:04:02 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putchar(char c, int *p, int fd)
{
	write(fd, &c, 1);
	*p += 1;
}

void	ft_printf_putstr(char *str, int *p, int fd)
{
	int	i;
	int	a;

	if (!str)
	{
		ft_printf_putstr("(null)", p, fd);
		return ;
	}
	i = ft_strlen(str);
	*p += i;
	a = 0;
	while (a < i)
		write(fd, &str[a++], 1);
}

void	ft_printf_putnbr(int n, char *str, int *p, int fd)
{
	unsigned int	nu;
	size_t			i;

	if (!str)
		return ;
	nu = n;
	i = ft_strlen(str);
	if (n < 0 && i != 16)
	{
		ft_printf_putchar('-', p, fd);
		nu = -n;
	}
	if (nu >= i)
	{
		ft_printf_putnbr(nu / i, str, p, fd);
		ft_printf_putnbr(nu % i, str, p, fd);
	}
	else
		ft_printf_putchar(str[nu], p, fd);
}

void	ft_printf_ptohex(void *p, int *o, int fd)
{
	ft_printf_putstr("0x", o, fd);
	ft_printf_putnbrun((unsigned long int)p, "0123456789abcdef", o, fd);
}
