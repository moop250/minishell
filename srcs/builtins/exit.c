/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:52:51 by pberset           #+#    #+#             */
/*   Updated: 2024/07/17 18:12:01 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_exit(t_core *core, char **in)
{
	unsigned int	i;

	i = 0;
	if (in[1])
	{
		i = ft_atoi(in[1]);
		if (!ft_isnumeric(in[1]))
		{
			ms_printerror(4, NULL);
			i = 2;
		}
		else if (in[2])
		{
			ms_printerror(3, NULL);
			return ;
		}
	}
	ms_freeall(core);
	exit(i);
}