/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:01:09 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 11:13:29 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core, char **env)
{
	int	child_pid;
	int	status;

	child_pid = fork();
	if (child_pid == -1)
		ms_error("fork error");
	if (child_pid == 0)
	{
		for (int i = 0; i < core->pipeline->param_count; i++)
			printf("params[%d]: %s\n", i, core->pipeline->params[i]);
		if (execve(/* should be /bin/cmd */, /* Should be "cmd", "param0", ...*/, env) == -1)
			ms_error("execve error");
	}
	else
		waitpid(child_pid, &status, 0);
}