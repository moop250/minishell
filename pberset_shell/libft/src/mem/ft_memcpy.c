/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:20:11 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"
#include <signal.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*str;

	if (dst == NULL || src == NULL)
		return (NULL);
	dest = (char *)dst;
	str = (const char *)src;
	while (n)
	{
		*dest = *str;
		dest++;
		str++;
		n--;
	}
	return (dst);
}
