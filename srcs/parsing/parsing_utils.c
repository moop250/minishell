/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/04 13:36:20 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ms_seperate_env(const char *in)
{
	char	*out;
	char	*tmp;
	size_t	i;

	i = 1;
	while (!ft_strchr(SEPERATOR, in[i]))
		++i;
	tmp = ft_substr(in, 1, i - 1);
	out = findenvvalue(tmp);
	gfree(tmp);
	return (out);
}

char	*strwrk(size_t pos[3], const char *in, char	*out)
{
	char	*tmp[2];

	tmp[0] = ft_substr(in, pos[1], pos[2] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	out = tmp[1];
	tmp[0] = ms_seperate_env(in + pos[2]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	out = tmp[1];
	return (out);
}

/*
	pos[0] = position for in
	pos[1] = start of current array section
	pos[2] = end of curent array section
*/

static char	*dbl_quotes(const char *in)
{
	size_t	pos[3];
	char	*tmp[2];
	char	*out;

	pos[0] = 0;
	pos[1] = 1;
	out = ft_strdup("");
	while (in[++pos[0]] != '"' && in[pos[0]])
	{
		if (in[pos[0]] == '$')
		{
			pos[2] = pos[0];
			out = strwrk(pos, in, out);
			while (in[++pos[0]] && !ft_strchr(SEPERATOR, in[pos[0]]))
				;
			pos[1] = pos[0];
			if (in[pos[0]] == '$')
				--pos[0];
			else if (in[pos[0]] == '"')
				++pos[1];
		}
	}
	tmp[0] = ft_substr(in, pos[1], pos[0] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	return (gfree(out), gfree(tmp[0]), tmp[1]);
}

static char	*sgl_quotes(const char *in)
{
	size_t	tmp;
	char	*out;

	tmp = 0;
	while (in[++tmp] != '\'')
		;
	out = ft_substr(in, 1, tmp - 1);
	return (out);
}

char	*quotewrk(const char *in)
{
	char	*out;

	if (in[0] == '"')
		out = dbl_quotes(in);
	else
		out = sgl_quotes(in);
	return (out);
}
