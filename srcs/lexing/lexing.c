/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/17 17:24:47 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quote_seperator(const char *input, const int start)
{
	int	pos;

	pos = start + 1;
	while (input[pos] && input[pos] != input[start])
		++pos;
	if (input[pos] == input[start])
			return (pos + 1);
	ms_printerror(ft_strjoin("no ending quote at ", ft_itoa(pos)));
	return (-1);
}

static int	seperator(const char *str, int pos)
{
	char	tmp;
	int		count;

	count = 1;
	if (ft_strchr(REDIRECTS, str[pos]))
	{
		tmp = str[pos];
		while (str[++pos] == tmp)
			++count;
		if (((tmp == '<' || tmp == '>') && count > 2) || (tmp == '|' && count > 1))
		{
			ms_printerror(ft_strjoin("ivalid redirection or pipe at ",
				ft_itoa(pos)));
			return (-1);
		}
	}
	else
	{
		while (str[pos] && !ft_strchr(WHITESPACE, str[pos]) && !ft_strchr(REDIRECTS, str[pos]))
			++pos;
	}
	return (pos);
}

int	tokenizer(const char *input, t_core *core)
{
	int		pos[2];
	int		i;

	i = 0;
	gfree(core->line);
	while (input[i])
	{
		while (input[i] && ft_strchr(WHITESPACE, input[i]))
			i++;
		pos[0] = i;
		if (ft_strchr(QUOTES, input[i]))
			pos[1] = quote_seperator(input, pos[0]);
		else
			 pos[1] = seperator(input, pos[0]);
		if (pos[1] == -1)
		{
			ms_tokensclear(core->token);
			return (-1);
		}
		ms_addtoken_back(core,
			ms_newtoken(ft_substr(input, pos[0], pos[1] - pos[0])));
		i = pos[1];
	}
	return (1);
}
