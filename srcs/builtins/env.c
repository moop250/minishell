/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/20 11:48:32 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_env(char **in, t_core *core)
{
	t_envparam	*tmp;

	if (in[1])
	{
		ms_printerror(3, NULL);
		core->exit_status = 1;
		return ;
	}
	tmp = core->env->rawenvs;
	while (tmp)
	{
		if (tmp->value)
			ft_printf_fd(STDOUT_FILENO, "%s%s=%s%s\n", ORANGE,
				tmp->name, tmp->value, CLEAR);
		tmp = tmp->next;
	}
	core->exit_status = 0;
}
