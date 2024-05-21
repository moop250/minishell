/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:45:21 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/21 17:24:32 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ms_newtoken(char *content)
{
	t_token	*node;

	node = galloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*ms_tokenlast(t_token *token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	ms_addtoken_back(t_core *core, t_token *new)
{
	t_token	*token;
	t_token	*tmp;

	token = core->token;
	if (!core->token)
		core->token = new;
	else
	{
		tmp = ms_tokenlast(token);
		new->prev = tmp;
		tmp->next = new;
	}
}

static void	ms_tokendelone(t_token *token)
{
	if (!token)
		return ;
	gfree(token->content);
	gfree(token);
	return ;
}

void	ms_tokensclear(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (token)
	{
		temp = token->next;
		ms_tokendelone(token);
		token = temp;
	}
	token = NULL;
	return ;
}
