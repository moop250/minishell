/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:03:41 by hlibine           #+#    #+#             */
/*   Updated: 2023/11/03 15:33:55 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static int	ft_comp(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		a;

	i = 0;
	a = 0;
	while (needle[a] == haystack[i] && i < len)
	{
		if (needle[a + 1] == '\0')
			return (1);
		a++;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	int			a;
	const char	*f;

	i = 0;
	a = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		f = haystack;
		if (needle[a] == haystack[i])
		{
			f = &haystack[i];
			if (ft_comp(&haystack[i], needle, len - i) == 1)
				return ((char *)f);
		}
		i++;
	}
	return (NULL);
}
