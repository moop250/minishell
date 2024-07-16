/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:23 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 15:27:44 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_solo(t_pipeline *pipeline, char **paths, char **env)
{
	pipeline->execp = init_execp(pipeline, paths);
	if (!pipeline->execp)
		exit(EXIT_FAILURE);
	if (execve(pipeline->execp, pipeline->params, env) < 0)
	{
		exec_err(NULL, pipeline->execp, "execve");
		exit(EXIT_FAILURE);
	}
}

void	execute_one(t_pipeline *pipeline, char **paths, char **env)
{
	pid_t	pid;
	int		status;
	int		buf_stdin;
	int		buf_stdout;

	buf_stdin = dup(STDIN_FILENO);
	buf_stdout = dup(STDOUT_FILENO);
	handle_files(pipeline);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_solo(pipeline, paths, env);
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			return ;
		}
		dup2(buf_stdin, STDIN_FILENO);
		close(buf_stdin);
		dup2(buf_stdout, STDOUT_FILENO);
		close(buf_stdout);
		if (pipeline->pipeline_in != NULL)
			close(pipeline->pipeline_in->fd);
		if (pipeline->pipeline_out != NULL)
			close(pipeline->pipeline_out->fd);
	}
}
