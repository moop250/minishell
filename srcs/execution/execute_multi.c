/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:37 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 17:38:43 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	clean_parent(pid_t child_pid, int *status, int pipe_fd[2], t_pipeline *current)
{
	if (current->next != NULL)
		close(pipe_fd[1]);
	if (current->prev != NULL)
		close(current->prev_fd);
	if (current->next != NULL)
		current->next->prev_fd = pipe_fd[0];
	if (waitpid(child_pid, status, 0) < 0)
		exec_err(pipe_fd, current->execp, "waitpid");
	exec_err(pipe_fd, current->execp, NULL);
	current = current->next;
}

void	execute_multi(t_pipeline *pipeline, char **paths, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	int 

	if ((child_pid = fork()) < 0)
	{
		exec_err(pipe_fd, NULL, "fork");
		return ;
	}
	if (child_pid == 0)
		exec_child(pipe_fd, current, core);
	else
		clean_parent(child_pid, &(core->exit_status), pipe_fd, current);
}