/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:56:23 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:33:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static int	ft_digicount(int n)
{
	int	out;

	out = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		out++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		out++;
	}
	return (out);
}

static char	*ft_out(char *out, int n, int i)
{
	char	temp;

	while (n > 0)
	{
		temp = (n % 10) + '0';
		out[i - 1] = temp;
		i--;
		n = n / 10;
	}
	return (out);
}

char	*ft_itoa(int n)
{
	char	*out;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_digicount(n);
	out = (char *)galloc(((i + 1) * sizeof(char)));
	if (out == NULL)
		return (NULL);
	if (n < 0)
	{
		out[0] = '-';
		n *= -1;
	}
	out = ft_out(out, n, i);
	out[i] = '\0';
	return (out);
}
