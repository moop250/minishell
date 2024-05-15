/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 14:24:24 by hlibine          ###   ########.fr       */
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
		if (!tokenizer(core->line, core))
			continue ;
		tmp = (*core->token);
		while (tmp)
		{
			ft_printf_fd(core->ms_stdout, "--->%s", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		ms_tokensclear(core->token);
		free(core->line);
	}
}
