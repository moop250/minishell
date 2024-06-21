/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:45:35 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 15:13:34 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

int	ft_putuint_fd(unsigned int n, int fd)
{
	int	check;

	check = 0;
	if (n > 9)
		check += ft_putuint_fd(n / 10, fd);
	check += ft_putchar_fd(n % 10 + '0', fd);
	return (check);
}
