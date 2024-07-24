/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:46:13 by pberset           #+#    #+#             */
/*   Updated: 2024/07/24 14:48:33 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_echo(char **in, t_core *core)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	core->exit_status = core->exit_status; //???
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
