/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:01:09 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 14:36:32 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core, char **env)
{
	int		child_pid;
	int		status;
	char	*exec_path;

	exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
	child_pid = fork();
	if (child_pid == -1)
		ms_error("fork error");
	if (child_pid == 0)
	{
		if (execve(exec_path, core->pipeline->params, env) == -1)
			ms_error("execve error");
	}
	else
		waitpid(child_pid, &status, 0);
}