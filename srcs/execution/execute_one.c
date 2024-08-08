/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:19:03 by pberset           #+#    #+#             */
/*   Updated: 2024/08/08 11:39:45 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_one(t_core *core)
{
	char	*execp;

	setup_signals(SIGQUIT, handle_sigquit);
	ft_printf_fd(1, "%l\n", foreground_pid);
	execp = init_execp(core->pipeline, core->env->paths);
	if (!execp)
	{
		ft_printf_fd(2, "%s: command not found\n", core->pipeline->params[0]);
		exit(127);
	}
	if (!ft_strcmp(execp, "builtin"))
	{
		free(execp);
		exit(execute_builtins(core));
	}
	if (execve(execp, core->pipeline->params, core->env->envp) < 0)
	{
		exec_err(NULL, execp, "execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
