/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extras.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:19:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/30 17:41:28 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*findenvvalue(char *in)
{
	t_envparam	*env;

	env = findenv(in);
	if (env == NULL)
		return (ft_strdup(""));
	return (ft_strdup(env->value));
}

t_envparam	*ms_cust_addenvend(t_envparam *param, char *name, char	*value, bool env)
{
	t_envparam	*tmp;
	t_envparam	*new;

	if (!value)
		new = ms_newenv(ft_strdup(name), NULL, env);
	else
		new = ms_newenv(ft_strdup(name), ft_strdup(value), env);
	if (!param)
		param = new;
	else
	{
		tmp = ms_lastenv(param);
		new->prev = tmp;
		tmp->next = new;
	}
	return (param);
}