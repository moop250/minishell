/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:10:57 by pberset           #+#    #+#             */
/*   Updated: 2024/07/15 13:50:49 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child(int **pipefd, int cmd_count, t_pipeline *current, t_env *env)
{
	int i = 0;
	if (i == 0 && cmd_count > 1)
	{
		dup2(pipefd[0][1], STDOUT_FILENO);
	}
	else if (i < cmd_count - 1)
	{
		dup2(pipefd[i-1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
	}
	else if (i == cmd_count - 1 && i > 0)
	{
		dup2(pipefd[i-1][0], STDIN_FILENO);
	}
	int j = 0;
	while (j < cmd_count - 1)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
	current->execp = init_execp(current, env->paths);
	execve(current->execp, current->params, env->envp);
	exec_err(NULL, current->execp, current->params[0]);
	exit(EXIT_FAILURE);
}
