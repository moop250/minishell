/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envvars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:24:10 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/04 17:03:15 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	treat_dollar(const char *in, t_list **list, size_t pos)
{
	size_t		out;
	char		*tmp;
	t_core		*core;

	out = 0;
	core = get_core();
	if (in[1] != '?')
	{
		while (in[++out] && !ft_strchr(SEPERATOR, in[out]))
			;
		tmp = ft_substr(in, 1, out - 1);
		ft_lstadd_back(list, ft_lstnew(findenvvalue(tmp)));
		gfree(tmp);
	}
	else
	{
		ft_lstadd_back(list, ft_lstnew(ft_itoa(core->exit_status)));
		pos += 2;
	}
	return (out + pos);
}

static size_t	treat_quote(const char *in, t_list **list, size_t pos)
{
	pos = quotewrk(in + pos, list);
	return (++pos);
}

size_t	treat_text(const char *in, t_list **list, size_t pos[2], int mode)
{
	if (mode == 0)
	{
		while (in[pos[0]] != '"' && in[pos[0]] != '\''
			&& in[pos[0]] != '$' && in[pos[0]])
			++pos[0];
	}
	else
		while (in[pos[0]] != '"' && in[pos[0]] != '$' && in[pos[0]])
			++pos[0];
	ft_lstadd_back(list, ft_lstnew(ft_substr(in, pos[1], pos[0] - pos[1])));
	return (pos[0]);
}

static char	*recombine(t_list *list)
{
	t_list	*tmp;
	char	*str;
	char	*out;

	out = ft_strdup("");
	tmp = list;
	while (tmp)
	{
		str = ft_strjoin(out, tmp->content);
		gfree(out);
		out = str;
		tmp = tmp->next;
	}
	ft_lstclear(&list);
	return (out);
}

/*
	pos[0] = position for in
	pos[1] = start of current array section
*/

char	*parse_envvars(const char *in)
{
	t_list	*list;
	size_t	pos[2];

	list = NULL;
	pos[0] = 0;
	pos[1] = 0;
	while (in[pos[0]])
	{
		if (in[pos[0]] == '\'' || in[pos[0]] == '"')
		{
			pos[0] += treat_quote(in, &list, pos[0]);
			pos[1] = pos[0];
		}
		else if (in[pos[0]] == '$')
		{
			pos[0] = treat_dollar(in + pos[0], &list, pos[0]);
			pos[1] = pos[0];
		}
		else
			pos[0] = treat_text(in, &list, pos, 0);
	}
	return (recombine(list));
}
