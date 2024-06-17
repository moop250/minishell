/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/17 16:22:20 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static void	setdelimiter(t_pipeline *pipe, t_token *token, int status)
{
	t_pipe_fd	*tmp;
	
	if (status == 1)
	{
		tmp = ms_addpipe_fd_back(pipe->pipeline_in);
		if (token->content[1])
			tmp->heredoc = true;
	}
	else
	{
		tmp = ms_addpipe_fd_back(pipe->pipeline_out);
		if (token->content[1])
			tmp->append = true;
	}
	tmp->file_name = ft_strdup(token->next->content);
	token = token->next;
}

static void	quotewrk(t_pipeline **pipe, t_token *token)
{
	char	*str;
	int		i;

	str = token->content;
	if (!(*pipe)->cmd)
		if (str[0] == '"' && str[1] == '$')
			(*pipe)->cmd = parse_quotes(str);
		else
			(*pipe)->cmd = ft_substr(str, 1, ft_strlen(str) - 2);
	else
	{
		i = (*pipe)->param_count;
		if (str[0] == '\'')
			(*pipe)->params[i] = ft_substr(str, 1, ft_strlen(str) - 2);
		else
			(*pipe)->params[i] = parse_quotes(str);
		++(*pipe)->param_count;
	}
}

static void	cmdwrk(t_pipeline **pipe, t_token *token)
{
	size_t	i;

	if (token->content[0] == '\'' || token->content[0] == '"')
		quotewrk(pipe, token);
	else if (!(*pipe)->cmd)
	{
		if (token->content[0] == '$')
			(*pipe)->cmd = findenv(++token->content)->value;
		else
			(*pipe)->cmd = ft_strdup(token->content);
	}
	else
	{
		i = (*pipe)->param_count;
		(*pipe)->params[i] = ft_strdup(token->content);
		(*pipe)->params[i + 1] = NULL;
		++(*pipe)->param_count;
	}
}

static int setparamcount(t_token *tmp)
{
	int		count;

	count = -1;
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

void	parser(t_core *core, t_token *token)
{
	t_pipeline	*pipe;

	while (token)
	{
		pipe = ms_addpipeline_back(core);
		pipe->params = galloc((setparamcount(token) + 1) * sizeof(char *));
		pipe->param_count = 0;
		while (token)
		{
			if (token->content[0] == '|')
			{
				token = token->next;
				break ;
			}
			else if (token->content[0] == '<')
				setdelimiter(pipe, token, 1);
			else if (token->content[0] == '>')
				setdelimiter(pipe, token, 2);
			else
				cmdwrk(&pipe, token);
			token = token->next;
		}
	}
	ms_tokensclear(&core->token);
}

