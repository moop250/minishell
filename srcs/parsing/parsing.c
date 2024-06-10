/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/10 17:55:41 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	inputdelimiter(t_core *core, t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_in);
	if (token->content[1])
		tmp->heredoc = true;
	tmp->file_name = ft_strdup(token->next->content);
	token = token->next;
}

static void	outputdelimiter(t_core *core, t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_out);
	if (token->content[1])
		tmp->heredoc = true;
	tmp->file_name = ft_strdup(token->next->content);
	token = token->next;
}

static void	quotewrk(t_core *core, t_pipeline *pipe, t_token *token)
{
	char	*str;
	int		i;

	str = token->content;
	i = -1;
	if (!pipe->cmd)
		pipe->cmd = ft_substr(str, 1, ft_strlen(str) - 2);
	else
	{
		while (pipe->params)
			++i;
		pipe->params = ft_realloc(pipe->params, i, (i + 1) * sizeof(char *));
		if (str[0] == '\'')
			pipe->params[++i] = ft_substr(str, 1, ft_strlen(str) - 2);
		else
			pipe->params[++i] = parse_quotes(str);
	}
}

static void	cmdwrk(t_core *core, t_pipeline *pipe, t_token *token)
{
	size_t	i;

	i = -1;
	if (token->content[0] == '\'' || token->content[0] == '"')
		quotewrk(core, pipe, token);
	else if (!pipe->cmd)
		pipe->cmd = ft_strdup(token->content);
	else
	{
		if (!pipe->params)
			pipe->params = galloc(sizeof(char *));
		else
		{
			while (pipe->params[i])
				++i;
			pipe->params = ft_realloc(pipe->params, i, i + 1);
		}
		pipe->params[++i] = ft_strdup(token->content);
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
				inputdelimiter(core, pipe, tmp);
			else if (tmp->content[0] == '>')
				outputdelimiter(core, pipe, tmp);
			else
				cmdwrk(core, pipe, tmp);
			tmp = tmp->next;
		}
	}
	ms_tokensclear(&token);
}

