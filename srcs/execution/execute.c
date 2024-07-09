/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/09 16:54:32 by pberset          ###   ########.fr       */
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

static void	exec_child(int i, t_core *core, int *fd, char **env)
{
	if (core->prev_fd != -1)
	{
		dup2(core->prev_fd, STDIN_FILENO);
		close(core->prev_fd);
	}
	close(fd[0]);
	if (i < core->pipe_count)
		dup2(fd[1], STDOUT_FILENO);
	if (execve(core->pipeline->execp, core->pipeline->params, env) == -1)
		perror("execve");
	close(fd[1]);
	exit(1);
}

static void	parental_cleaning(t_core *core, int *fd)
{
	if (core->prev_fd != -1)
		close(core->prev_fd);
	core->prev_fd = fd[0];
	close(fd[1]);
	if (core->pipeline->pipeline_out \
		&& core->pipeline->pipeline_out->fd != -1)
	{
		close(core->pipeline->pipeline_out->fd);
		core->pipeline->pipeline_out->fd = -1;
	}
	if (core->pipeline->execp)
	{
		gfree(core->pipeline->execp);
		core->pipeline->execp = NULL;
	}
}

static void	pipe_loop(t_core *core, int *child_pid, char **env)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i <= core->pipe_count)
	{
		handle_files(core->pipeline);
		if (core->pipeline->params)
			core->pipeline->execp = init_execp(core);
		if (core->pipeline->params)
		{
			if (pipe(fd) == -1)
				perror("pipe");
			child_pid[i] = fork();
			if (child_pid[i] == -1)
				perror("fork");
			if (child_pid[i] == 0)
				exec_child(i, core, fd, env);
		}
		parental_cleaning(core, fd);
		if (core->pipeline->next)
			core->pipeline = core->pipeline->next;
		i++;
	}
}

void	execute(t_core *core, char **env)
{
	int			*child_pid;
	int			i;
	t_pipeline	*tmp_pipe;
	int			b_stdin;
	int			b_stdout;

	tmp_pipe = core->pipeline;
	core->prev_fd = -1;
	child_pid = (int *)malloc((core->pipe_count + 1) * sizeof(int));
	if (!child_pid)
		ms_error("malloc error\n");
	b_stdin = dup(STDIN_FILENO);
	b_stdout = dup(STDOUT_FILENO);
	pipe_loop(core, child_pid, env);
	i = 0;
	while (i <= core->pipe_count)
	{
		waitpid(child_pid[i], &(core->exit_status), 0);
		i++;
	}
	free(child_pid);
	core->pipeline = tmp_pipe;
	dup2(b_stdin, STDIN_FILENO);
	dup2(b_stdout, STDOUT_FILENO);
}
