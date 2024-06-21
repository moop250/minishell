/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:20:27 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	if (dst == NULL && src == NULL)
		return (dst);
	dest = (char *)dst;
	source = (const char *)src;
	if (dest > source)
	{
		dest += n;
		source += n;
		while (n--)
			*--dest = *--source;
	}
	else
	{
		while (n--)
			*dest++ = *source++;
	}
	return (dst);
}
