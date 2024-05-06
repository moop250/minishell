/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/06 16:01:40 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ms_isspace(char c)
{
	if (c == ' ' || &c == "\n" || &c == "\t")
		return (true);
	return (false);
}

static int	quote_seperator(const char *input, const int start)
{
	int	pos;

	pos = start + 1;
	while (input[pos] && input[pos] != input[start])
		++pos;
	if (input[pos] == input[start])
			return (pos + 1);
	ms_error(ft_strjoin("no ending quote at ", ft_itoa(pos)));
}

static int	seperator(const char *str, int pos)
{
	char	tmp;
	int		count;

	count = 1;
	if (str[pos] == '<' || str[pos] == '>' || str[pos] == '|')
	{
		tmp = str[pos];
		while (str[++pos] == tmp)
			++count;
		if (((tmp == '<' || tmp == '>') && count > 2) || (tmp == '|' && count > 1))
			ms_error(ft_strjoin("ivalid redirection or pipe at ",
				ft_itoa(pos)));
	}
	else
	{
		while (str[pos] && !ms_isspace(str[pos]) && str[pos] != '>'
			&& str[pos] != '<'&& str[pos] != '|' && str[pos] != '\"'
			&& str[pos] != '\'')
			++pos;
	}
	return (pos);
}

char	**tokenizer(const char *input, t_core *core)
{
	int		pos[2];
	int		i;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		while (ms_isspace(input[i]) == true)
			i++;
		pos[0] = i;
		if (input[i] == '\"' || input[i] == '\'')
			pos[1] = quote_seperator(input, pos[0]);
		else
			 pos[1] = seperator(input, pos[0]);
		ms_addtoken_back(core,
			ms_newtoken(ft_substr(input, pos[0], pos[1] - pos[0])));
		i = pos[1];
	}
}
