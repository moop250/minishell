/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:05 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/02 17:41:50 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	isspace(char c)
{
	if (c == ' ' || c == "\n" || c == "\t")
		return (true);
	return (false);
}

int	quote_seperator(const char *input, const int start)
{
	int	pos;

	pos = start + 1;
	while (input[pos] && input[pos] != input[start])
		++pos;
	return (pos);
}

int	seperator(const char *str, int pos)
{
	char	tmp;
	int		count;

	count = 1;
	if (str[pos] == '<' || str[pos] == '>' || str[pos] == '|')
	{
		tmp = str[pos];
		while (str[++pos] == tmp)
			++count;
		if (((tmp == '<' || tmp == '>') && count < 2)
			|| tmp == '|' && count < 1);
			ms_error(ft_strjoin("ivalid redirection or pipe at ",
				ft_itoa(pos)));
	}
	else
	{
		while (str[pos] && !isspace(str[pos]) && str[pos] != '>'
			&& str[pos] != '<'&& str[pos] != '|' && str[pos] != '\"'
			&& str[pos] != '\'')
			++pos;
		pos -= 1;
	}
	return (pos);
}

char	**tokenizer(const char *input, t_core *core)
{
	int		pos[2];
	int		i;
	bool	quote;

	i = -1;
	quote == false;
	while (input[++i])
	{
		while (isspace(input[i]) == true)
			i++;
		pos[0] = i;
		if (input[i] == '\"' || input[i] == '\'')
			pos[1] = quote_seperator(input, pos[0]);
		else
			 pos[1] = seperator(input, &quote, pos[0]);
		addtokenend(core, ft_substr(input, pos[0], pos[1] - pos[0]));
	}
}
