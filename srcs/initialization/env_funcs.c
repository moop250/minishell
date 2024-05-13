/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:49 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/13 17:25:38 by hlibine          ###   ########.fr       */
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

	name = ft_substr(in, 0, sep - 1);
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