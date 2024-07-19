/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:32 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 18:34:21 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_pipes(int pipes[2][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i % 2][0]);
		close(pipes[i % 2][1]);
		i++;
	}
}

int	handle_redirections(t_pipeline *cmd)
{
	if (handle_files(cmd) != 0)
		return (1);
	return (0);
}

int	init_pipes(int pipes[2][2], int i, int pipe_count)
{
	if ( i > 0)
	{
		if (dup2(pipes[(i - 1) % 2][0], STDIN_FILENO) < 0)
			return (1);
	}
	if (i < pipe_count)
	{
		if (dup2(pipes[i % 2][1], STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}
