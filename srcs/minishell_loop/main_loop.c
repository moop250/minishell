/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/03 18:12:51 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_loop(t_core *core)
{
	t_token	*tmp;

	while (true)
	{
		core->prompt = readline("minishell: $ ");
		if (!core->prompt)
			ms_error("readline error");
		tokenizer(core->prompt, core);
		tmp = (*core->token);
		while (tmp)
		{
			printf("--->%s", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		ms_tokensclear(core->token);
		free(core->prompt);
		break;
	}
}
