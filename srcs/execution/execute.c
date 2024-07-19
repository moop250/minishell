/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 15:17:37 by pberset          ###   ########.fr       */
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
			if (setup_pipes(core->pipeline, pipes, i, core->pipe_count) != 0)
				exit(EXIT_FAILURE);
			if (handle_redirections(core->pipeline) != 0)
				exit(EXIT_FAILURE);
			close_pipes(pipes, core->pipe_count);
			execute_one(core->pipeline, core->env->paths, core->env->envp);
		}
		core->pipeline = core->pipeline->next;
		i++;
	}
	close_pipes(pipes, core->pipe_count);
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
