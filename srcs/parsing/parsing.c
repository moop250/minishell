/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/24 17:55:19 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static void	quotewrk(t_pipeline **pipe, t_token *token)
{
	char	*str;
	char	*tmp;
	int		i;

	str = token->content;
	i = (*pipe)->param_count;
	if (str[1] == '$' && str[0] == '"')
	{
		tmp = ft_substr(str, 2, ft_strlen(str) - 3);
		(*pipe)->params[i] = ft_strdup(findenvvalue(tmp));
	}
	else if (str[0] == '\'')
		(*pipe)->params[i] = ft_substr(str, 1, ft_strlen(str) - 2);
	else
		(*pipe)->params[i] = parse_quotes(str);
	(*pipe)->params[i + 1] = NULL;
	++(*pipe)->param_count;
}

static void	cmdwrk(t_pipeline **pipe, t_token *token)
{
	size_t	i;

	if (token->content[0] == '\'' || token->content[0] == '"')
		quotewrk(pipe, token);
	else
	{
		i = (*pipe)->param_count;
		if (token->content[0] == '$')
			(*pipe)->params[i] = ft_strdup(findenvvalue(token->content + 1));
		else
			(*pipe)->params[i] = ft_strdup(token->content);
		(*pipe)->params[i + 1] = NULL;
		++(*pipe)->param_count;
	}
}

static int	setparamcount(t_token *tmp)
{
	int		count;

	count = 0;
	while (tmp && tmp->content[0] != '|')
	{
		if (tmp->content[0] == '<' || tmp->content[0] == '>')
			tmp = tmp->next;
		else
			++count;
		tmp = tmp->next;
	}
	return (count);
}

static void	passpipes(t_pipeline **pipe, t_token **token)
{
	if ((*token)->content[0] == '<')
		setdelimiter(pipe, token, 1);
	else if ((*token)->content[0] == '>')
		setdelimiter(pipe, token, 2);
	else
		cmdwrk(pipe, (*token));
}

void	parser(t_core *core, t_token *token)
{
	t_pipeline	*pipe;
	int			tmp;

	while (token)
	{
		pipe = ms_addpipeline_back(core);
		tmp = setparamcount(token);
		if (tmp > 0)
			pipe->params = galloc((tmp + 1) * sizeof(char *));
		pipe->param_count = 0;
		while (token)
		{
			if (token->content[0] == '|')
			{
				token = token->next;
				break ;
			}
			passpipes(&pipe, &token);
			token = token->next;
		}
	}
	ms_tokensclear(&core->token);
}
