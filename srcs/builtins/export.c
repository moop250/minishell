/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 13:29:26 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(void)
{

}

void	ms_export(char **in, t_core *core)
{
	size_t		i;
	t_envparam	*param;

	i = 0;
	if (in[1] == NULL)
		print_export();
	while (in[++i])
	{
		param = findenv(in[i]);
		if (!param)
			addenvend(core, in[i], false);
		else
		{
			gfree(param->value);
			param->value = ft_strdup(in[i]);
		}
	}
	core->exit_status = 0;
}
