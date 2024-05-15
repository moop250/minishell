/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:49 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 16:27:31 by hlibine          ###   ########.fr       */
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

void	addenvend(t_core *core, char *in, int sep, bool env)
{
	t_envparam	**token;
	t_envparam	*tmp;
	t_envparam	*new;
	char		*name;
	char		*value;

	name = ft_substr(in, 0, sep);
	value = ft_substr(in, sep + 1, ft_strlen(in) - sep);
	new = ms_newenv(name, value, env);
	token = core->env->rawenvs;
	if (!*core->env->rawenvs)
		*token = new;
	else
	{
		tmp = ms_lastenv(*token);
		new->prev = tmp;
		tmp->next = new;
	}
}

t_envparam	*findenv(const char *name)
{
	t_core	*core;
	t_envparam	*out;

	core = get_core();
	out = *core->env->rawenvs;
	while (out)
	{
		if (ft_strcmp(name, out->name) == 0)
			return (out);
		out = out->next;
	}
	return (NULL);
}

void	modifenv(t_envparam *env, const char *str)
{
	gfree(env->value);
	env->value = ft_strdup(str);
}