/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:49:12 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	c_pos;

	i = 0;
	c_pos = -1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			c_pos = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	if (c_pos == -1)
		return (NULL);
	return ((char *)(s + c_pos));
}
