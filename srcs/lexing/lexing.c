/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/28 13:50:45 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static int	quote_seperator(const char *input, const int start)
{
	int	pos;

	pos = start + 1;
	while (input[pos] && input[pos] != input[start])
		++pos;
	if (input[pos] == input[start])
		return (pos + 1);
	ms_printerror(0, "tmp error while i figure out the mini heredoc");
	return (-1);
}

static int	seperator(const char *str, int pos)
{
	char	tmp[2];
	int		count;

	count = 1;
	tmp[1] = '\0';
	if (ft_strchr(REDIRECTS, str[pos]))
	{
		tmp[0] = str[pos];
		while (str[++pos] == tmp[0])
			++count;
		if (((tmp[0] == '<' || tmp[0] == '>') && count > 2)
			|| (tmp[0] == '|' && count > 1))
		{
			ms_printerror(1, tmp);
			return (-1);
		}
	}
	else
	{
		while (str[pos] && !ft_strchr(WHITESPACE, str[pos])
			&& !ft_strchr(REDIRECTS, str[pos]))
			++pos;
	}
	return (pos);
}

static int	tokenizer_loop(t_core *core, char *input)
{
	int	pos[2];
	int	i;

	i = 0;
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
			ms_tokensclear(&core->token);
			return (-1);
		}
		ms_addtoken_back(core,
			ms_newtoken(ft_substr(input, pos[0], pos[1] - pos[0])));
		i = pos[1];
		++core->token_count;
	}
	return (1);
}

static int	tokenizer_checker(t_core *core)
{
	t_token	*tmp;
	char	errms[2];

	tmp = core->token;
	while (tmp)
	{
		if ((tmp->content[0] == '<' || tmp->content[0] == '>') && !tmp->next)
		{
			ms_printerror(1, "\\n");
			return (-1);
		}
		else if ((tmp->content[0] == '<' || tmp->content[0] == '>')
			&& (tmp->next->content[0] == '<' || tmp->next->content[0] == '>'
				|| tmp->next->content[0] == '|'))
		{
			errms[0] = tmp->next->content[0];
			errms[1] = '\0';
			ms_printerror(1, errms);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	tokenizer(char *input, t_core *core)
{
	int	i;

	core->token_count = 0;
	gfree(core->line);
	i = tokenizer_loop(core, input);
	gfree(input);
	if (i < 0)
		return (i);
	i = tokenizer_checker(core);
	if (core->token)
		if (core->token->content[0] == '|')
		{
			ms_printerror(1, "|");
			i = -1;
		}
	if (i < 0)
		ms_tokensclear(&core->token);
	return (i);
}
