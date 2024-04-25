/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:50:50 by hlibine           #+#    #+#             */
/*   Updated: 2023/11/03 15:32:05 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	ft_out(const char *str, int i, int n)
{
	int	o;

	o = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		o = o * 10 + (str[i] - '0');
		i++;
	}
	return (o * n);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (str[0] == '\0')
		return (0);
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (ft_isdigit(str[i + 1]) != 1)
			return (0);
		else if (str[i] == '-')
			n *= -1;
		i++;
	}
	if ((ft_strncmp(&str[i], "2147483647", 10) == 0) && n != -1)
		return (2147483647);
	return (ft_out(str, i, n));
}
