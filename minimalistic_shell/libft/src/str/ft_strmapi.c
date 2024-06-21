/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:48 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*output;

	i = 0;
	output = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!output)
		return (NULL);
	while (s[i])
	{
		output[i] = (unsigned char)f(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
