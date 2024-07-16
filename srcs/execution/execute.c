/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 15:34:54 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core)
{
	int	buf_in;
	int	buf_out;

	buf_in = dup(STDIN_FILENO);
	buf_out = dup(STDOUT_FILENO);
	if (core->pipeline == NULL)
		return ;
	if (core->pipeline->next == NULL)
		execute_one(core->pipeline, core->env->paths, core->env->envp);
	else
		execute_multi(core->pipe_count + 1, core->pipeline, core->env);
	dup2(buf_in, STDIN_FILENO);
	dup2(buf_out, STDOUT_FILENO);
}
