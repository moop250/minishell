/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/01 15:35:50 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inputdelimiter(t_core *core, t_pipeline *pipe, t_token *token)
{
	t_pipe_fd	*tmp;
	char		*input;

	tmp = ms_addpipe_fd_back(pipe, pipe->pipeline_in);
	if (input[1])
		tmp->heredoc = true;
	else
	{
		input = token->next->content;
		tmp->heredoc = false;
		tmp->file_name = ft_strdup(input);
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
				outputdelimiter();
			else
				cmdwrk();
			tmp = tmp->next;
		}
	}
}