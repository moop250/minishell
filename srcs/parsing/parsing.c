/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:37 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/30 19:25:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser(t_core *core, t_token *token)
{
	t_token	*tmp;
	t_pipeline	pipe;

	tmp = token;
	while(token)
	{
		ms_addpipeline_back(core);
		while (token)
		{
			if (token->content[0] = '|')
			{
				token = token->next;
				break;
			}
			else if (token->content[0] = '<')
				inputdelimiter();
			else if (token->content[0] = '>')
				outputdelimiter();
			else
				cmdwrk();
			token = token->next;
		}
	}
}