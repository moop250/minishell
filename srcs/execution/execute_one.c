/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:23 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 11:50:55 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_solo(t_pipeline *pipeline, char **paths, char **env)
{
	handle_files(pipeline);
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
	}
}
