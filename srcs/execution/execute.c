/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/01 16:22:09 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core, char **env)
{
	int		fd[2];
	int		*child_pid;
	int		i;
	t_pipeline	*tmp_pipe;

	i = 0;
	tmp_pipe = core->pipeline;
	core->prev_fd = -1;
	child_pid = (int *)malloc((core->pipe_count + 1) * sizeof(int));
	if (!child_pid)
		ms_error("malloc error\n");
	while (i <= core->pipe_count)
	{
		if (!access(core->pipeline->params[0], X_OK))
			core->pipeline->execp = core->pipeline->params[0];
		else
			core->pipeline->execp = find_exec_path(core->pipeline->params[0], core->env->paths);
		if (pipe(fd) == -1)
			ms_error("pipe error\n");
		child_pid[i] = fork();
		if (child_pid[i] == -1)
			ms_error("child error\n");
		if (child_pid[i] == 0)
		{
			if (core->prev_fd != -1)
			{
				dup2(core->prev_fd, STDIN_FILENO);
				close(core->prev_fd);
			}
			if (i < core->pipe_count)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (execve(core->pipeline->execp, core->pipeline->params, env) == -1)
				ms_error("execve error\n");
		}
		else
		{
			if (core->prev_fd != -1)
				close(core->prev_fd);
			close(fd[1]);
			core->prev_fd = fd[0];
		}
		free(core->pipeline->execp);
		core->pipeline = core->pipeline->next;
		i++;
	}
	i = 0;
	while (i++ <= core->pipe_count)
			waitpid(child_pid[i], &(core->exit_status), 0);
	free(child_pid);
	core->pipeline = tmp_pipe;
}
