/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:33:27 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/17 15:43:14 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

/*
Takes a string as input
Returns a 1 if the entire string is comprised of digits
Returns a 0 if the string contains non numeric characters
 */
int	ft_isnumeric(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}