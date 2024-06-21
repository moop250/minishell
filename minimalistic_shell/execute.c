/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:03:12 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 10:19:27 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_solo.h"

void	execute(t_commands *cmd)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		mega_free(cmd);
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd->exec_path, cmd->argv, cmd->envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(child_pid, NULL, 0);
}
