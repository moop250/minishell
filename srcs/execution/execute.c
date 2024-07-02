/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/01 18:57:17 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*init_execp(t_core *core)
{
	if (access(core->pipeline->params[0], X_OK) == 0)
		return (core->pipeline->params[0]);
	return (find_exec_path(core->pipeline->params[0], core->env->paths));
}

static void	exec_child(int i, t_core *core, int *fd, char **env)
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

static void	pipe_loop(t_core *core, int *child_pid, char **env)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i <= core->pipe_count)
	{
		core->pipeline->execp = init_execp(core);
		if (pipe(fd) == -1)
			ms_error("pipe error\n");
		child_pid[i] = fork();
		if (child_pid[i] == -1)
			ms_error("child error\n");
		if (child_pid[i] == 0)
			exec_child(i, core, fd, env);
		else
		{
			if (core->prev_fd != -1)
				close(core->prev_fd);
			close(fd[1]);
			core->prev_fd = fd[0];
		}
		core->pipeline = core->pipeline->next;
		i++;
	}
}

void	execute(t_core *core, char **env)
{
	int			*child_pid;
	int			i;
	t_pipeline	*tmp_pipe;

	tmp_pipe = core->pipeline;
	core->prev_fd = -1;
	child_pid = (int *)malloc((core->pipe_count + 1) * sizeof(int));
	if (!child_pid)
		ms_error("malloc error\n");
	pipe_loop(core, child_pid, env);
	i = 0;
	while (i++ <= core->pipe_count)
		waitpid(child_pid[i], &(core->exit_status), 0);
	free(child_pid);
	core->pipeline = tmp_pipe;
}
