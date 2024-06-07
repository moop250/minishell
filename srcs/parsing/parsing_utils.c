/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/07 18:40:51 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <time.h>

static char*	ms_merge(char **in)
{
	char	*out;
	int		i;

	while (in[++i])
		gfree(in[i]);
	return (out);
}

static char	**ms_seperate_env(const char *in, char **list)
{
	char	**out;
	size_t	i;
 	
	i = 1;
	while (!ft_strchr(SEPERATOR, in[i]))
		++i;
	out = ft_substr(in, 0, i);
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
	char	**tmp;
	size_t	i;

	pos[0] = 0;
	pos[1] = 1;
	tmp = galloc(sizeof(char *));
	tmp[0] = NULL;
	i = 1;
	while (in[++pos[0]])
	{
		if (in[pos[0]] == '$')
		{
			pos[2] = pos[0] - 1;
			tmp = ft_realloc(tmp, i, i + 1);
			tmp[i - 1] = ft_substr(in, pos[1], pos[2] - pos[1]);
			++i;
			tmp = ms_seperate_env(in, tmp);
			while (!ft_strchr(++pos[0]))
		}
	}
	tmp[i] = NULL;
	return (ms_merge(tmp));
}

