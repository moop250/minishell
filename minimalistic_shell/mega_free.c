/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:46:39 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 10:14:38 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_solo.h"

void	mega_free(t_commands *cmd)
{
	if (cmd->argv)
		ft_free_tab(cmd->argv);
	if (cmd->path)
		ft_free_tab(cmd->path);
	if (cmd->exec_path)
		free(cmd->exec_path);
	if (cmd)
		free(cmd);
}
