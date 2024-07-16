/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:32 by pberset           #+#    #+#             */
/*   Updated: 2024/07/15 16:10:16 by pberset          ###   ########.fr       */
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

int	**init_pipes(int cmd_count)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)ft_calloc(cmd_count - 1, sizeof(*pipefd));
	if (!pipefd)
	{
		exec_err(NULL, NULL, "pipefd");
		return (NULL);
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		pipefd[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipefd[i]) < 0)
		{
			exec_err(NULL, NULL, "pipe");
			free_pipes(pipefd, i);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}
