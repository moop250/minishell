/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:46:13 by pberset           #+#    #+#             */
/*   Updated: 2024/07/22 14:06:19 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_echo(char **in, t_core *core)
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
		ft_printf_fd(core->ms_stdout, "%s", in[i]);
		if (in[i + i])
			ft_printf_fd(core->ms_stdout, " ");
	}
	if (!flag)
		ft_printf_fd(core->ms_stdout, "\n");
	return (0);
}
