/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:17:16 by pberset           #+#    #+#             */
/*   Updated: 2024/08/20 20:32:25 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	close_pipes(int i, int pipe_count, int pipes[2][2])
{
	if (i > 0)
	{
		if (close(pipes[(i - 1) % 2][0]) < 0)
		{
			perror("close pipes");
			return (-1);
		}
	}
	if (i < pipe_count)
	{
		if (close(pipes[i % 2][1]) < 0)
		{
			perror("close pipes");
			return (-2);
		}
	}
	return (0);
}

static int	child_exec(t_core *core, int pipes[2][2], int i)
{
	int	status;

	core->interact = 0;
	child_signals();
	if (i < core->pipe_count || i > 0)
		init_pipes(core->pipeline, pipes, i, core->pipe_count);
	status = handle_redirections(core, core->pipeline);
	if (status != 0)
		exit(EXIT_FAILURE);
	else
		exit(execute_one(core));
}

static void	parent_wait(int pipe_count, int *status, pid_t *pid)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		waitpid(pid[i], status, 0);
		if (WIFSIGNALED(*status))
		{
			if (WTERMSIG(*status) == 3)
			{
				write(STDOUT_FILENO, "Quit (core dump)\n", 17);
				*status = 128 + 3;
			}
			else
			{
				printf("\33[2K\r");
				*status = 128 + 2;
			}
		}
	}
}

static char	*last_cmd(t_pipeline *pipeline)
{
	return (pipeline->params[pipeline->param_count - 1]);
}

int	execute(t_core *core)
{
	int		pipes[2][2];
	int		i;
	int		status;
	pid_t	*pid;

	if (!core->pipe_count && is_builtin(core->pipeline->params[0]))
		return (execute_builtins(core));
	pid = (pid_t *)galloc((core->pipe_count + 1) * sizeof(pid_t));
	i = -1;
	while (++i < core->pipe_count + 1)
	{
		modifenv(findenv("_"), ft_strdup(last_cmd(core->pipeline)));
		if (i < core->pipe_count)
			pipe(pipes[i % 2]);
		pid[i] = fork();
		if (pid[i] == 0)
			child_exec(core, pipes, i);
		close_pipes(i, core->pipe_count, pipes);
		core->pipeline = core->pipeline->next;
	}
	parent_wait(core->pipe_count + 1, &status, pid);
	gfree(pid);
	return (WEXITSTATUS(status));
}
