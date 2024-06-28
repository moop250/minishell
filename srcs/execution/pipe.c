/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/06/28 15:14:37 by pberset          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_core *core, char **env)
{
	int		fd[2];
	int		prev_fd;
	int		*child_pid;
	int		i;
	char	*exec_path;

	i = 0;
	prev_fd = -1;
	child_pid = (int *)malloc((core->pipe_count + 1) * sizeof(int));
	if (!child_pid)
		ms_error("malloc error\n");
	while (i <= core->pipe_count)
	{
		exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
		if (pipe(fd) == -1)
			ms_error("pipe error\n");
		child_pid[i] = fork();
		if (child_pid[i] == -1)
			ms_error("child error\n");
		if (child_pid[i] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < core->pipe_count)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (execve(exec_path, core->pipeline->params, env) == -1)
				ms_error("execve error\n");
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			close(fd[1]);
			prev_fd = fd[0];
		}
		free(exec_path);
		core->pipeline = core->pipeline->next;
		i++;
	}
	i = 0;
	while (i++ <= core->pipe_count)
			waitpid(child_pid[i], &(core->exit_status), 0);
	free(child_pid);
}
