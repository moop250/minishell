/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:40:24 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 14:55:35 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*output;
	char	*output_start;

	output = (char *)malloc(sizeof(char) * (ft_strlen(s1, '\0') + 1));
	if (!output)
		return (NULL);
	output_start = output;
	while (*s1)
	{
		*output = *s1;
		output++;
		s1++;
	}
	*output = 0;
	return (output_start);
}
