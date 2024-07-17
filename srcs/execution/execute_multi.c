/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:37 by pberset           #+#    #+#             */
/*   Updated: 2024/07/17 12:35:58 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_all_pipes(int **pipefd, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (close(pipefd[j][0]) < 0)
		{
			exec_err(pipefd[j], NULL, "close pipefd[j][0]");
			exit(EXIT_FAILURE);
		}
		if (close(pipefd[j][1]) < 0)
		{
			exec_err(pipefd[j], NULL, "close pipefd[j][1]");
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

void	execute_multi(int cmd_count, t_pipeline *pipeline, t_env *env)
{
	int			**pipefd;
	int			i;
	pid_t		*pid;
	t_pipeline	*current;
	int			status;

	pipefd = init_pipes(cmd_count);
	if (!pipefd)
		return ;
	current = pipeline;
	pid = (pid_t *)ft_calloc(cmd_count, sizeof(pid_t));
	if (!pid)
	{
		free_pipes(pipefd, cmd_count - 1);
		exec_err(NULL, NULL, "pid");
		return ;
	}
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			exec_err(NULL, NULL, "fork");
			return ;
		}
		if (pid[i] == 0)
		{
			handle_files(current);
			if (i == 0 && cmd_count > 1)
			{
				if (current->pipeline_out)
				{
					dup2(pipefd[i][1], current->pipeline_out->fd);
					close(current->pipeline_out->fd);
				}
				else
					dup2(pipefd[i][1], STDOUT_FILENO);
			}
			else if (i < cmd_count - 1)
			{
				dup2(pipefd[i - 1][0], STDIN_FILENO);
				if (current->pipeline_out)
				{
					dup2(pipefd[i][1], current->pipeline_out->fd);
					close(current->pipeline_out->fd);
				}
				else
					dup2(pipefd[i][1], STDOUT_FILENO);
			}
			else if (i == cmd_count - 1 && i > 0)
				dup2(pipefd[i - 1][0], STDIN_FILENO);
			close_all_pipes(pipefd, cmd_count);
			current->execp = init_execp(current, env->paths);
			if (current->execp)
				execve(current->execp, current->params, env->envp);
			exec_err(NULL, current->execp, current->params[0]);
			exit(EXIT_FAILURE);
		}
		current = current->next;
		i++;
	}
	close_all_pipes(pipefd, cmd_count);
	free_pipes(pipefd, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
}
