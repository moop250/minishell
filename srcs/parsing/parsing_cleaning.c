/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaning.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:18:27 by hlibine           #+#    #+#             */
/*   Updated: 2024/08/19 18:27:32 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static void	param_seperator(const char *str, size_t *num)
{
	size_t	pos;
	char	tmp;

	pos = num[0];
	if (ft_strchr(QUOTES, str[pos]))
	{
		++num[0];
		tmp = str[pos];
		while (str[++pos] && str[pos] != tmp)
			;
		num[1] = pos;
		return ;
	}
	while ((str[pos] && !ft_strchr(WHITESPACE, str[pos]) && !ft_strchr(QUOTES, str[pos])))
		++pos;
	num[1] = pos;
}

static int	findsize(const char *str)
{
	char	quote;
	int		count;
	int		i;

	quote = '\0';
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			++i;
		if (str[i] && str[i] == '"' && str[i] == '\'')
			quote = str[i];
		if (str[i])
			++count;
		while (str[i] && (str[i] != ' ' || (str[i] != quote && quote != '\0')))
			++i;
		if (str[i] && str[i] == quote)
		{
			++i;
			quote = '\0';
		}
	}
	printf("%i\n", count);
	return (count);
}

static char	**cleaner_loop(char *input)
{
	size_t		pos[2];
	int			i;
	int			a;
	char		**out;

	a = -1;
	i = 0;
	out = galloc((findsize(input) + 1) * sizeof(char *));
	while (input[i])
	{
		while (input[i] && ft_strchr(WHITESPACE, input[i]))
			i++;
		pos[0] = i;
		param_seperator(input, pos);
		out[++a] = ft_substr(input, pos[0], pos[1] - pos[0]);
		i = pos[1];
		if (input[i] == '"')
			++i;
		printf("%s%%\n", out[a]);
	}
	out[a + 1] = NULL;
	return (out);
}

void	ms_clean(t_pipeline **pipe)
{
	char	*tmp;
	char	*out;
	size_t	i;

	i = -1;
	out = ft_strdup("");
	while ((*pipe)->params[++i])
	{
		tmp = ft_strjoin(out, " ");
		gfree(out);
		out = ft_strjoin(tmp, (*pipe)->params[i]);
	}
	ft_2dfree((void **)(*pipe)->params);
	(*pipe)->params = cleaner_loop(out);
	gfree(out);
}
