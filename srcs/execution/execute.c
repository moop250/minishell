/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 11:56:50 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*init_execp(t_core *core)
{
	if (!core->pipeline->params)
		return (NULL);
	if (access(core->pipeline->params[0], X_OK) == 0)
		return (core->pipeline->params[0]);
	return (find_exec_path(core->pipeline->params[0], core->env->paths));
}

void	execute(t_core *core, char **env)
{
	t_pipeline	*start;
	pid_t		child_pid;
	int			status;
	int			pipe_fd[2];

	if (core->pipeline == NULL)
		return ;
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return ;
	}
	start = core->pipeline;
	while (core->pipeline != NULL)
	{
		if ((child_pid = fork()) < 0)
		{
			perror("fork");
			return ;
		}
		if (child_pid == 0)
		{
			core->pipeline->execp = init_execp(core);
			if (execve(core->pipeline->execp, core->pipeline->params, env) < 0)
				perror(core->pipeline->params[0]);
			exit(EXIT_FAILURE);
		}
		else
			if (waitpid(child_pid, &status, 0) < 0)
				perror("waitpid");
	}
}
