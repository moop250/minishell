/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/06/26 21:30:25 by pberset          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_core *core, char **env)
{
	int		fd[2];
	int		child1_pid;
	int		child2_pid;
	int		i;
	char	*exec_path;

	i = 0;
	while (i < core->pipe_count)
	{
		exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
		if (pipe(fd) == -1)
			ms_error("pipe error\n");
		child1_pid = fork();
		if (child1_pid == -1)
			ms_error("child1 error\n");
		if (child1_pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (execve(exec_path, core->pipeline->params, env) == -1)
				ms_error("execve1 error\n");
		}
		if (core->pipeline->next)
		{
			core->pipeline = core->pipeline->next;
			exec_path = find_exec_path(core->pipeline->params[0], core->env->paths);
			child2_pid = fork();
			if (child2_pid == -1)
				ms_error("child2 error\n");
			if (child2_pid == 0)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[1]);
				close(fd[0]);
				if (execve(exec_path, core->pipeline->params, env) == -1)
					ms_error("execve2 error\n");
			}
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(child1_pid, NULL, 0);
		waitpid(child2_pid, NULL, 0);
		i++;
	}
}
