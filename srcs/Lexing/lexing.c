/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/30 14:33:18 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	isspace(char c)
{
	if (c == ' ' || c == "\n" || c == "\t")
		return (true);
	return (false);
}

char	**tokenizer(char *input, t_core *core)
{
	int		start;
	int		end;
	int		i;
	bool	quote;

	i = -1;
	quote == false;
	while (input[++i])
	{
		while (isspace(input[i]) == true)
			i++;
		start = i;
		if (input[i] == '\"' || input[i] == '\'')
			quote == true;
		while (seperator(input[++i], &quote) == false)
			end = i;
		addtokenend(core, ft_substr(input, start, end - start));
	}
}
