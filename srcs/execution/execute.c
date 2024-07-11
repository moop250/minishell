/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:44 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 17:01:58 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_core *core)
{
	if (core->pipeline == NULL)
		return ;
	if (core->pipeline->next == NULL)
		execute_one(core->pipeline, core->env->paths, core->env->envp);
	else
		execute_multi(core->pipeline, core->env->paths, core->env->envp);
}
