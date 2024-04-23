/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/23 16:44:09 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	*init(int ac)
{
	t_core	*core;

	if (ac > 1)
		ms_error("minishell called with argument");
	core = galloc(sizeof(t_core));
	core->env = galloc(3 * sizeof(char *));
	core->env[0] = getenv("USER");
	core->env[1] = getenv("NAME");
	core->env[2] = getenv("PATH");
	return (core);
}