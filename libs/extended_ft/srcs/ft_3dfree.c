/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3dfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:11:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:43:20 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

void	ft_3dfree(void ***array)
{
	int		i;
	int		a;

	i = 0;
	while (array[i])
	{
		a = 0;
		while (array[i][a])
		{
			gfree(array[i][a]);
			++a;
		}
		gfree(array[i]);
		++i;
	}
	gfree(array);
}
