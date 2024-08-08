/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:17:16 by pberset           #+#    #+#             */
/*   Updated: 2024/08/08 11:51:46 by pberset          ###   ########.fr       */
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
	struct termios	child_tmodes;

	if (i < core->pipe_count || i > 0)
		init_pipes(core->pipeline, pipes, i, core->pipe_count);
	handle_redirections(core->pipeline);
	return (execute_one(core));
}

static int	parent_wait(int pipe_count, int *status, pid_t *pid)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
		waitpid(pid[i], status, WUNTRACED);
}

int	execute(t_core *core)
{
	int		pipes[2][2];
	int		i;
	int		status;
	pid_t	*pid;

	pid = (pid_t *)galloc((core->pipe_count + 1) * sizeof(pid_t));
	if (!core->pipe_count && is_builtin(core->pipeline->params[0]))
		return (execute_builtins(core));
	i = -1;
	while (++i < core->pipe_count + 1)
	{
		modifenv(findenv("_"), ft_strdup(core->pipeline->params[core->pipeline->param_count - 1]));
		if (i < core->pipe_count)
			pipe(pipes[i % 2]);
		pid[i] = fork();
		if (pid[i] == 0)
			child_exec(core, pipes, i);
		foreground_pid = pid[i];
		tcgetattr(STDIN_FILENO, &(core->shell_tmode));
		close_pipes(i, core->pipe_count, pipes);
		core->pipeline = core->pipeline->next;
	}
	parent_wait(core->pipe_count + 1, &status, pid);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(core->shell_tmode));
	foreground_pid = 0;
	gfree(pid);
	return (WEXITSTATUS(status));
}
