/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:46:10 by hlibine           #+#    #+#             */
/*   Updated: 2023/11/03 15:33:51 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if ((s1[0] == '\0' && s2[0] == '\0') || n == 0)
		return (0);
	else if (s1[0] == '\0' || s2[0] == '\0')
		return (s3[0] - s4[0]);
	while (i++ < n)
	{
		if (s3[i - 1] != s4[i - 1])
			return (s3[i - 1] - s4[i - 1]);
		else if (s3[i] == '\0' || s4[i] == '\0')
			if (i < n)
				return (s3[i] - s4[i]);
	}
	return (0);
}
