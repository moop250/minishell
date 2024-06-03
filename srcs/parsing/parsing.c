/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/03 16:39:21 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inputdelimiter(t_core *core, t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_in);
	if (token->content[1])
		tmp->heredoc = true;
	tmp->file_name = ft_strdup(token->next->content);
}

static void	outputdelimiter(t_core *core, t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;

	tmp = ms_addpipe_fd_back(pipe->pipeline_out);
	if (token->content[1])
		tmp->heredoc = true;
	tmp->file_name = ft_strdup(token->next->content);
}

static void	cmdwrk(t_core *core, t_pipeline *pipe, t_token *token)
{
	size_t	i;

	i = -1;
	if (!pipe->cmd)
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

char	*parser(t_core *core, t_token *token)
{
	t_token		*tmp;
	t_pipeline	*pipe;

	tmp = token;
	while(tmp)
	{
		pipe = ms_addpipeline_back(core);
		while (tmp)
		{
			if (tmp->content[0] = '|')
			{
				tmp = tmp->next;
				break;
			}
			else if (tmp->content[0] = '<')
				inputdelimiter(core, pipe, tmp);
			else if (tmp->content[0] = '>')
			{
				outputdelimiter(core, pipe, tmp);
				tmp = tmp->next;
			}
			else
				cmdwrk(core, pipe, tmp);
			tmp = tmp->next;
		}
	}
}