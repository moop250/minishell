/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/11 15:03:25 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	inputdelimiter(t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_in);
	if (token->content[1])
		tmp->heredoc = true;
	tmp->file_name = ft_strdup(token->next->content);
	token = token->next;
}

static void	outputdelimiter(t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_out);
	if (token->content[1])
		tmp->append = true;
	tmp->file_name = ft_strdup(token->next->content);
	token = token->next;
}

static void	quotewrk(t_pipeline *pipe, t_token *token)
{
	char	*str;
	int		i;

	str = token->content;
	if (!pipe->cmd)
		if (str[0] == '"' && str[1] == '$')
			pipe->cmd = parse_quotes(str);
		else
			pipe->cmd = ft_substr(str, 1, ft_strlen(str) - 2);
	else
	{
		i = pipe->param_count;
		pipe->params = ft_realloc(pipe->params, i, (i + 1) * sizeof(char *));
		if (str[0] == '\'')
			pipe->params[++i] = ft_substr(str, 1, ft_strlen(str) - 2);
		else
			pipe->params[++i] = parse_quotes(str);
		++pipe->param_count;
	}
}

static void	cmdwrk(t_pipeline *pipe, t_token *token)
{
	size_t	i;

	if (token->content[0] == '\'' || token->content[0] == '"')
		quotewrk(pipe, token);
	else if (!pipe->cmd)
	{
		if (token->content[0] == '$')
			pipe->cmd = findenv(++token->content)->value;
		else
			pipe->cmd = ft_strdup(token->content);
	}
	else
	{
		i = pipe->param_count;
		pipe->params = ft_realloc(pipe->params, i, (i + 1) * sizeof(char *));
		pipe->params[++i] = ft_strdup(token->content);
		++pipe->param_count;
	}
}

void	parser(t_core *core, t_token *token)
{
	t_token		*tmp;
	t_pipeline	*pipe;

	tmp = token;
	while (tmp)
	{
		pipe = ms_addpipeline_back(core);
		while (tmp)
		{
			if (tmp->content[0] == '|')
			{
				tmp = tmp->next;
				break ;
			}
			else if (tmp->content[0] == '<')
				inputdelimiter(pipe, tmp);
			else if (tmp->content[0] == '>')
				outputdelimiter(pipe, tmp);
			else
				cmdwrk(pipe, tmp);
			tmp = tmp->next;
		}
		if (pipe->param_count > 0)
		{
			pipe->params = ft_realloc(pipe->params, pipe->param_count,
				(pipe->param_count + 1) * sizeof(char *));
			pipe->params[pipe->param_count + 1] = NULL;
		}
	}
	ms_tokensclear(&token);
}

