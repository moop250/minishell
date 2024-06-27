/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/06/27 17:26:31 by pberset          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_core *core, char **env)
{
	int		fd[2];
	int		prev_fd;
	int		child_pid;
	int		i;
	char	*exec_path;

	i = 0;
	prev_fd = -1;
	while (i <= core->pipe_count)
	{
		exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
		if (pipe(fd) == -1)
			ms_error("pipe error\n");
		child_pid = fork();
		if (child_pid == -1)
			ms_error("child error\n");
		if (child_pid == 0)
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
	while (++i <= core->pipe_count)
		wait(NULL);
}
