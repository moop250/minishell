/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:52:05 by pberset           #+#    #+#             */
/*   Updated: 2024/07/22 14:00:35 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"

int	execute_builtins(t_core *core)
{
	if (!ft_strcmp(core->pipeline->params[0], "cd"))
	{
		ft_printf_fd(2, "cd: Not implemented yet\n");
		return (1);
	}
	if (!ft_strcmp(core->pipeline->params[0], "echo"))
		ms_echo(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "env"))
		ms_env(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "exit"))
		ms_exit(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "export"))
		ms_export(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "pwd"))
		ms_pwd(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "unset"))
		ms_unset(core->pipeline->params);
	return (core->exit_status);
}
