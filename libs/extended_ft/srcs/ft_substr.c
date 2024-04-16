/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:55:08 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:33:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s) - start;
	if ((size_t)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len < l)
		out = galloc(len + 1);
	else
		out = galloc(l + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < l && s[i] != '\0' && i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
