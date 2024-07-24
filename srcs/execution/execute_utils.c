/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:16:52 by pberset           #+#    #+#             */
/*   Updated: 2024/07/24 15:08:42 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	handle_redirections(t_pipeline *cmd)
{
	if (handle_files(cmd) != 0)
		return (1);
	return (0);
}

int	init_pipes(t_pipeline *cmd, int pipes[2][2], int i, int pipe_count)
{
	if (cmd->prev)
	{
		if (dup2(pipes[(i - 1) % 2][0], STDIN_FILENO) < 0)
		{
			close(pipes[(i - 1) % 2][0]);
			return (1);
		}
	}
	if (cmd->next)
	{
		if (dup2(pipes[i % 2][1], STDOUT_FILENO) < 0)
		{
			close(pipes[i % 2][1]);
			return (1);
		}
	}
	if (i > 0)
		close(pipes[(i - 1) % 2][1]);
	if (i < pipe_count)
		close(pipes[i % 2][0]);
	return (0);
}
