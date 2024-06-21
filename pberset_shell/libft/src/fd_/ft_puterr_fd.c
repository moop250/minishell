/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:16:09 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

#define ANSI_COLOR_BOLD_RED	"\033[1;31m"
#define ANSI_COLOR_RESET	"\033[0m"

int	ft_puterr_fd(char *s)
{
	int		check;

	check = 0;
	if (!s)
		ft_puterr_fd("(null)");
	write(STDERR_FILENO, ANSI_COLOR_BOLD_RED, 7);
	while (*s)
	{
		check += ft_putchar_fd(*s, STDERR_FILENO);
		s++;
	}
	write(STDERR_FILENO, ANSI_COLOR_RESET, 4);
	return (check);
}
