/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:19:03 by pberset           #+#    #+#             */
/*   Updated: 2024/07/28 21:27:49 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_one(t_core *core)
{
	char	*execp;

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
