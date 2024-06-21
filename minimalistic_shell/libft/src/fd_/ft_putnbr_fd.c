/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:45:35 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	check;

	check = 0;
	if (n == INT_MIN)
	{
		check = write(fd, "-2147483648", 11);
		return (check);
	}
	if (n < 0)
	{
		check += write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		check += ft_putnbr_fd(n / 10, fd);
	check += ft_putchar_fd(n % 10 + '0', fd);
	return (check);
}
