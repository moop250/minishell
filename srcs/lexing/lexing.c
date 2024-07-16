/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/15 14:13:35 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static size_t	param_seperator(const char *str, const int start)
{
	bool	quotes;
	size_t	pos;
	char	lst[2];

	quotes = false;
	pos = start;
	lst[1] = '\0';
	lst[0] = '\0';
	while ((str[pos] && !ft_strchr(WHITESPACE, str[pos])
			&& !ft_strchr(REDIRECTS, str[pos])) || (str[pos] && quotes))
	{
		if ((str[pos] == '"' || str[pos] == '\'') && !quotes)
		{
			quotes = true;
			lst[0] = str[pos];
		}
		else if (str[pos] == lst[0] && quotes)
			quotes = false;
		++pos;
	}
	if (quotes)
		return (ms_printerror(2, lst), -1);
	return (pos);
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
		pos = param_seperator(str, pos);
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
		if ((tmp->content[0] == '<' || tmp->content[0] == '>'
				|| tmp->content[0] == '|') && !tmp->next)
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
	{
		if (core->token->content[0] == '|')
		{
			ms_printerror(1, "|");
			i = -1;
		}
	}
	if (i < 0)
		ms_tokensclear(&core->token);
	return (i);
}
