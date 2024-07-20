/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:25:18 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 23:24:09 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_err(int *pipe_fd, char *execp, char *msg)
{
	struct stat	st;
	int			i;

	if (msg)
		perror(msg);
	i = 0;
	if (pipe_fd)
	{
		while (i < 2)
		{
			if (fstat(pipe_fd[i], &st) == 0)
			{
				if (close(pipe_fd[i]) < 0)
					perror("close");
			}
			else
			{
				if (errno != EBADF)
					perror("fstat");
			}
			i++;
		}
	}
	if (execp)
		free(execp);
}
