/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:59:29 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 14:45:42 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

size_t	ft_strlen(const char *s, const char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while ((unsigned char)s[len] != (unsigned char)c)
		len++;
	return (len);
}
