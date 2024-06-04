/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:49 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/04 11:50:37 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envparam	*ms_newenv(char *name, char *value, bool env)
{
	t_envparam	*node;

	node = galloc(sizeof(t_envparam));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->base = env;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_envparam	*ms_lastenv(t_envparam *token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	addenvend(t_core *core, char *in, bool env)
{
	t_envparam	*tmp;
	t_envparam	*new;
	char		*name;
	char		*value;
	int			i;

	i = 0;
	while (in[i] && in[i] != '=')
		++i;
	name = ft_substr(in, 0, i);
	value = ft_substr(in, i + 1, ft_strlen(in) - i);
	new = ms_newenv(name, value, env);
	if (!core->env->rawenvs)
		core->env->rawenvs = new;
	else
	{
		tmp = ms_lastenv(core->env->rawenvs);
		new->prev = tmp;
		tmp->next = new;
	}
}

t_envparam	*findenv(const char *name)
{
	t_core		*core;
	t_envparam	*out;

	core = get_core();
	out = core->env->rawenvs;
	while (out)
	{
		if (ft_strcmp(name, out->name) == 0)
			return (out);
		out = out->next;
	}
	return (NULL);
}

//takes a MALLOC'd string
void	modifenv(t_envparam *env, char *str)
{
	t_envparam	**tmp;

	if (!env || !str)
		return ;
	tmp = &env;
	gfree((*tmp)->value);
	(*tmp)->value = ft_strdup(str);
	gfree(str);
}

