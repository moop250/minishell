/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:52:05 by pberset           #+#    #+#             */
/*   Updated: 2024/07/28 11:43:33 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"

int	execute_builtins(t_core *core)
{
	int	status;

	if (!ft_strcmp(core->pipeline->params[0], "cd"))
		status = ms_cd(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "echo"))
		status = ms_echo(core->pipeline->params);
	if (!ft_strcmp(core->pipeline->params[0], "env"))
		status = ms_env(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "exit"))
		ms_exit(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "export"))
		status = ms_export(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "pwd"))
		status = ms_pwd(core->pipeline->params, core);
	if (!ft_strcmp(core->pipeline->params[0], "unset"))
		status = ms_unset(core->pipeline->params);
	return (status);
}
