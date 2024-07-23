/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/23 15:14:36 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	test(pid_t pid, int pipe, char *msg)
{
	while (pid < 0 || pipe < 0)
	{
		perror(msg);
		return (1);
	}
	return (0);
}

static void	err(int handle, char *msg)
{
	if (handle != 0)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

static void	close_pipes(int i, int pipe_count, int pipes[2][2])
{
	if (i > 0)
		test(0, close(pipes[(i - 1) % 2][0]), "close");
	if (i < pipe_count)
		test(0, close(pipes[i % 2][1]), "close");
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute(t_core *core)
{
	int		pipes[2][2];
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < core->pipe_count + 1)
	{
		if (i < core->pipe_count)
			test(0, pipe(pipes[i % 2]), "pipe");
		if (is_builtin(core->pipeline->params[0]))
			return (execute_builtins(core));
		pid = fork();
		test(pid, 0, "fork");
		if (pid == 0)
		{
			err(init_pipes(core->pipeline, pipes, i, core->pipe_count), "pipe");
			err(handle_redirections(core->pipeline), "redirections");
			execute_one(core);
		}
		close_pipes(i, core->pipe_count, pipes);
		core->pipeline = core->pipeline->next;
		i++;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
