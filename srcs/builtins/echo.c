/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:46:13 by pberset           #+#    #+#             */
/*   Updated: 2024/07/26 18:52:14 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_echo(char **in)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (in[1])
	{
		if (in[1][0] == '-' && in[1][1] == 'n' && in[1][2] == '\0')
		{
			++i;
			flag = true;
		}
	}
	while (in[++i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s", in[i]);
		if (in[i + i])
			ft_printf_fd(STDOUT_FILENO, " ");
	}
	if (!flag)
		ft_printf_fd(STDOUT_FILENO, "\n");
	return (0);
}
