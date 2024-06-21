/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:22:33 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	if (needle[0] == 0)
		return ((char *)haystack);
	h = 0;
	while (haystack[h] && h < len)
	{
		n = 0;
		while (haystack[h + n] == needle[n] && n + h < len)
		{
			if (!needle[n + 1])
				return ((char *)haystack + h);
			n++;
		}
		h++;
	}
	return (NULL);
}
