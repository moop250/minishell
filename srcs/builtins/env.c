/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/17 17:40:57 by hlibine          ###   ########.fr       */
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
			ft_printf_fd(core->ms_stdout, "%s%s=%s%s\n", ORANGE,
				tmp->name, tmp->value, CLEAR);
		tmp = tmp->next;
	}
	core->exit_status = 0;
}
