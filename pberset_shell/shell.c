/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:52:01 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 15:24:00 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_solo.h"

void	shell(char *input, char **envp)
{
	t_commands	*cmd;

	cmd = (t_commands *)malloc(sizeof(t_commands));
	if (!cmd)
		return ;
	cmd->pipe_count = count_pipes(input);
	printf("%ld\n", cmd->pipe_count);
	init_cmd(cmd, input, envp);
	if (!cmd)
		return ;
	execute(cmd);
	mega_free(cmd);
}
