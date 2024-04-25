/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:51:48 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:43:20 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			a++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (a);
}

static char	*ft_strwrk(char const *s, char c, int a)
{
	int		i;
	char	*out;

	i = 0;
	while (s[a + i] != c && s[a + i])
		i++;
	out = ft_substr(s, a, i);
	if (!out)
		return (NULL);
	return (out);
}

static char	**ft_free(char **out, int i)
{
	while (i)
	{
		gfree(out[i]);
		i--;
	}
	gfree(out);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i;
	int		a;

	i = 0;
	a = 0;
	out = galloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	while (s[a])
	{
		while (s[a] == c && s[a])
			a++;
		if (s[a] != c && s[a] && i < ft_wordcount(s, c))
		{
			out[i++] = ft_strwrk(s, c, a);
			if (out[i - 1] == NULL)
				return (ft_free(out, i - 1));
		}
		while (s[a] != c && s[a])
			a++;
	}
	out[i] = NULL;
	return (out);
}
