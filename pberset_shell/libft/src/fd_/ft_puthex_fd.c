/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:46:54 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 15:13:34 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

int	ft_puthex_fd(unsigned long n, int up, int fd)
{
	int		check;
	char	hex_symbols[17];

	check = 0;
	if (up)
		ft_strlcpy(hex_symbols, "0123456789ABCDEF", 17);
	else
		ft_strlcpy(hex_symbols, "0123456789abcdef", 17);
	if (n >= 16)
		check += ft_puthex_fd(n / 16, up, fd);
	check += ft_putchar_fd(hex_symbols[n % 16], fd);
	return (check);
}
