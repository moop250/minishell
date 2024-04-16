/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:13 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:33:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static int	ft_limits(char const *s1, char const *set, int start)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1[start] == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strmkr(const char *s1, int s, int e)
{
	char	*out;
	int		i;

	if (s >= ft_strlen(s1))
		return (ft_strdup(""));
	out = galloc (e - s + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (s + i < e)
	{
		out[i] = s1[s + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;

	if (ft_strlen(s1) == 0 || (!s1))
		return (ft_strdup(""));
	s = 0;
	e = ft_strlen(s1) - 1;
	while (ft_limits(s1, set, s))
		s++;
	while (ft_limits(s1, set, e))
		e--;
	return (ft_strmkr(s1, s, e + 1));
}
