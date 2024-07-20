/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:46:13 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 11:14:21 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_echo(char **in, t_core *core)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (in[1][0] == '-' && in[1][1] == 'n' && in[1][2] == '\0')
	{
		++i;
		flag = true;
	}
	while (in[++i])
	{
		if ((!flag && i == 1) || (flag && i == 2))
			ft_printf_fd(core->ms_stdout, " ");
		ft_printf_fd(core->ms_stdout, "%s", in[i]);
	}
	if (!flag)
		ft_printf_fd(core->ms_stdout, "\n");
	core->exit_status = 0;
}
