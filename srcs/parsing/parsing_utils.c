/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/06 17:19:45 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*seperate_quotes(const char *in)
{
	char	*out;
 
	
	return (out);
}

char	*parse_quotes(char *in)
{
	char	*out;
	int		i;
	int		outlen;
	char	*tmp;

	i = -1;
	outlen = -1;
	while (in[++i])
	{
		if (in[i] == '$')
		{
			tmp = seperate_env()
			outlen += strelen(findenv())
			while (!ft_strcmp([i]))
				++i;
		}
		else
			++outlen;
	}
	return (out);
}

