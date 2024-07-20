/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:23 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 11:03:53 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_one(t_core *core)
{
	core->pipeline->execp = init_execp(core->pipeline, core->env->paths);
	if (!core->pipeline->execp)
	{
		ft_printf_fd(2, "%s: command not found\n", core->pipeline->params[0]);
		exit(127);
	}
	if (!ft_strcmp(core->pipeline->execp, "builtin"))
		exit(execute_builtins(core));
	if (execve(core->pipeline->execp, core->pipeline->params, core->env->envp) < 0)
	{
		exec_err(NULL, core->pipeline->execp, "execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
