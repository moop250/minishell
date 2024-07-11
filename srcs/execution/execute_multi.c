/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:37 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 19:00:42 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	clean_parent(pid_t child_pid, int *status, int pipe_fd[2], t_pipeline *current)
{
	struct stat	st;

	if (fstat(pipe_fd[1], &st) == 0)
		if (close(pipe_fd[1]) < 0)
			exec_err(pipe_fd, NULL, "close pipe_fd[1]");
	if (current->prev != NULL)
		if (close(current->prev_fd) < 0)
			exec_err(pipe_fd, NULL, "close prev_fd");
	if (current->next != NULL)
		current->next->prev_fd = pipe_fd[0];
	if (fstat(pipe_fd[0], &st) == 0)
		if (close(pipe_fd[0]) < 0)
			exec_err(pipe_fd, NULL, "close pipe_fd[0]");
	if (waitpid(child_pid, status, 0) < 0)
	{
		exec_err(pipe_fd, current->execp, "waitpid");
		return ;
	}
	current = current->next;
}

void	execute_multi(t_pipeline *pipeline, char **paths, char **env)
{
	int			pipefd[2];
	pid_t		pid;
	t_pipeline	*current;
	int			status;

	current = pipeline;
	pipeline->prev_fd = -1;
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			if (pipe(pipefd) < 0)
			{
				exec_err(pipefd, NULL, "pipe");
				return ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			exec_err(pipefd, NULL, "fork");
			return ;
		}
		if (pid == 0)
		{
			if (current->prev != NULL)
			{
				if (dup2(current->prev_fd, STDIN_FILENO) < 0)
				{
					exec_err(pipefd, NULL, "dup2 prev_fd");
					exit(EXIT_FAILURE);
				}
				if (close(current->prev_fd) < 0)
				{
					exec_err(pipefd, NULL, "close prev_fd");
					exit(EXIT_FAILURE);
				}
			}
			if (current->next != NULL)
			{
				if(dup2(pipefd[1], STDOUT_FILENO) < 0)
				{
					exec_err(pipefd, NULL, "dup2 pipefd[1]");
					exit(EXIT_FAILURE);
				}
				if (close(pipefd[0]) < 0)
				{
					exec_err(pipefd, NULL, "close pipefd[0]");
					exit(EXIT_FAILURE);
				}
				if (close(pipefd[1]) < 0)
				{
					exec_err(pipefd, NULL, "close pipefd[1]");
					exit(EXIT_FAILURE);
				}
			}
			current->execp = init_execp(current, paths);
			execve(current->execp, current->params, env);
			exec_err(pipefd, current->execp, current->params[0]);
			exit(EXIT_FAILURE);
		}
		else
			clean_parent(pid, &status, pipefd, current);
	}
}
