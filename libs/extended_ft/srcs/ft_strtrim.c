/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:12:13 by hlibine           #+#    #+#             */
/*   Updated: 2024/08/20 15:09:13 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;

	if (!s1)
		return (ft_strdup(""));
	e = ft_strlen(s1);
	if (e == 0)
		return (ft_strdup(""));
	s = 0;
	while (s1[s] && ft_strchr(set, s1[s]))
		++s;
	while (e && ft_strchr(set, s1[--e]))
		;
	return (ft_substr(s1, s, e + 1 - s));
}
