/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 23:14:33 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute(t_core *core)
{
	int		pipes[2][2];
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < core->pipe_count + 1)
	{
		if (i < core->pipe_count && pipe(pipes[i % 2]) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (init_pipes(core->pipeline, pipes, i, core->pipe_count) != 0)
				exit(EXIT_FAILURE);
			if (handle_redirections(core->pipeline) != 0)
				exit(EXIT_FAILURE);
			execute_one(core);
		}
		if (i > 0)
			close(pipes[(i - 1) % 2][0]);
		if (i < core->pipe_count)
			close(pipes[i % 2][1]);
		core->pipeline = core->pipeline->next;
		i++;
	}
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
