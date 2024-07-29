/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:17:16 by pberset           #+#    #+#             */
/*   Updated: 2024/07/29 12:56:42 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	close_pipes(int i, int pipe_count, int pipes[2][2])
{
	if (i > 0)
		if (close(pipes[(i - 1) % 2][0]) < 0)
		{
			perror("close pipes");
			return (-1);
		}
	if (i < pipe_count)
		if (close(pipes[i % 2][1]) < 0)
		{
			perror("close pipes");
			return (-2);
		}
	return (0);
}

static int	child_exec(t_core *core, int pipes[2][2], int i, t_pipeline *tmp)
{
	if (i < core->pipe_count || i > 0)
		init_pipes(tmp, pipes, i, core->pipe_count);
	handle_redirections(core->pipeline);
	return (execute_one(core));
}

int	execute(t_core *core)
{
	int		pipes[2][2];
	int		i;
	int		status;
	pid_t	pid;
	t_pipeline	*tmp;

	if (!core->pipe_count && is_builtin(core->pipeline->params[0]))
		return (execute_builtins(core));
	i = 0;
	tmp = core->pipeline;
	while (i < core->pipe_count + 1)
	{
		if (i < core->pipe_count)
			pipe(pipes[i % 2]);
		pid = fork();
		if (pid == 0)
			child_exec(core, pipes, i, tmp);
		else
			waitpid(pid, &status, 0);
		close_pipes(i, core->pipe_count, pipes);
		tmp = tmp->next;
		i++;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
