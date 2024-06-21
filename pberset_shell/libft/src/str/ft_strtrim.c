/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:57:32 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

static int	ft_setcmp(char c, char const *c_set)
{
	int	i;

	i = 0;
	while (c_set[i])
	{
		if (c_set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*output;
	size_t	start;
	size_t	end;
	int		i;

	start = 0;
	while (s1[start] && ft_setcmp(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_setcmp(s1[end - 1], set))
		end--;
	i = 0;
	output = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!output)
		return (NULL);
	while (start < end)
	{
		output[i] = s1[start];
		i++;
		start++;
	}
	output[i] = '\0';
	return (output);
}
