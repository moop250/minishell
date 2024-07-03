/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/03 16:23:59 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	cmdwrk(t_pipeline **pipe, t_token *token)
{
	size_t	i;

	i = (*pipe)->param_count;
	(*pipe)->params[i] = parse_envvars(token->content);
	(*pipe)->params[i + 1] = NULL;
	++(*pipe)->param_count;
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

	core->pipe_count = 0;
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
				core->pipe_count++;
				break ;
			}
			passpipes(&pipe, &token);
			token = token->next;
		}
	}
	ms_tokensclear(&core->token);
}
