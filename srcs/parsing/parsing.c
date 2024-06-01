/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/31 16:09:30 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inputdelimiter(t_core *core, t_pipeline *pipe)
{
	pipe->pipeline_in
}

char	*parser(t_core *core, t_token *token)
{
	t_token		*tmp;
	t_pipeline	*pipe;

	tmp = token;
	while(token)
	{
		pipe = ms_addpipeline_back(core);
		while (token)
		{
			if (token->content[0] = '|')
			{
				token = token->next;
				break;
			}
			else if (token->content[0] = '<')
				inputdelimiter(core, pipe);
			else if (token->content[0] = '>')
				outputdelimiter();
			else
				cmdwrk();
			token = token->next;
		}
	}
}