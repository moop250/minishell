/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:10:57 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 16:28:44 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child(int pipe_fd[2], t_pipeline *current, t_core *core)
{
	if (current->prev != NULL)
	{
		if (dup2(current->prev_fd, STDIN_FILENO) < 0)
		{
			exec_err(pipe_fd, NULL, "dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (current->next != NULL)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		{
			exec_err(pipe_fd, NULL, "dup2");
			exit(EXIT_FAILURE);
		}
		exec_err(pipe_fd, NULL, NULL);
	}
	current->execp = init_execp(current, core->env->paths);
	if (!current->execp)
	{
		exec_err(pipe_fd, NULL, NULL);
		ms_error("exec path not found");
	}
	if (execve(current->execp, current->params, core->env->envp) < 0)
		exec_err(pipe_fd, current->execp, "execve");
	exit(EXIT_FAILURE);
}