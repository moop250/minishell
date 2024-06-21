/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:32:00 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	size;
	char	*start;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (size + 1));
	if (!join)
		return (NULL);
	start = join;
	while (s1 && *s1)
	{
		*join = (unsigned char)*s1;
		join++;
		s1++;
	}
	while (s2 && *s2)
	{
		*join = (unsigned char)*s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (start);
}
