/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/10 17:49:44 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <time.h>

static char	*ms_seperate_env(const char *in)
{
	char	*out;
	size_t	i;
 	
	i = 1;
	while (!ft_strchr(SEPERATOR, in[i]))
		++i;
	out = ft_substr(in, 0, i);
	return (out);
}

static char	*strwrk(int pos[3], const char *in, char	*out)
{
	char	*tmp;

	tmp[0] = ft_substr(in, pos[1], pos[2] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	out = tmp[1];
	tmp[0] = ms_seperate_env(in);
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

char	*parse_quotes(char *in)
{
	char	*out;
	size_t	pos[3];
	char	*tmp[2];

	pos[0] = 0;
	pos[1] = 1;
	out = ft_strdup("");
	while (in[++pos[0]] && in[pos[0]] != '"')
	{
		if (in[pos[0]] == '$')
		{
			pos[2] = pos[0] - 1;
			out = strwrk(pos, in, out);
			while (!ft_strchr(SEPERATOR, in[pos[0]]))
				++pos[0];
			pos[1] = pos[0];
		}
	}
	tmp[0] = ft_substr(in, pos[1], pos[0] - pos[1]); 
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	return (tmp[1]);
}

