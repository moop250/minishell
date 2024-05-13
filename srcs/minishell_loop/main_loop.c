/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/13 14:36:10 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_loop(t_core *core)
{
	t_token	*tmp;

	while (true)
	{
		core->line = readline(core->prompt->prompt);
		if (!core->line)
			ms_error("readline error");
		if (!tokenizer(core->line, core));
			continue ;
		tmp = (*core->token);
		while (tmp)
		{
			printf("--->%s", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		ms_tokensclear(core->token);
		free(core->line);
	}
}
