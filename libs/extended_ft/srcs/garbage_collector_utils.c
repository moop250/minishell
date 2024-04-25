/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gargabe_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:46:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:19:22 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

t_garbcol	*lastgarbage(t_garbcol *garb)
{
	if (!garb)
		return (0);
	while (garb->next)
		garb = garb->next;
	return (garb);
}
