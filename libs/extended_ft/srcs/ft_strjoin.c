/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:51:02 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:33:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*out;

	i = 0;
	out = galloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (NULL);
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		if (i < ft_strlen(s1))
			out[i] = s1[i];
		else
			out[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	out[i] = '\0';
	return (out);
}
