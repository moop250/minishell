/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/23 16:04:28 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(t_core *core)
{
	t_envparam	*tmp;

	tmp = core->env->rawenvs;
	while (tmp)
	{
		if (tmp->base == true)
			ft_printf_fd(core->ms_stdout, "%s%s=%s%s\n", ORANGE, tmp->name, tmp->value, CLEAR);
		tmp = tmp->next;
	}
}
