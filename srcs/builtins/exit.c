/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:52:51 by pberset           #+#    #+#             */
/*   Updated: 2024/07/30 15:29:22 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_exit(char **in, t_core *core)
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
			return (1);
		}
	}
	ms_freeall(core);
	exit(i);
}
