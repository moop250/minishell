/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/30 11:23:22 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	*init(int ac, char **env)
{
	t_core	*core;

	if (ac > 1)
		ms_error("minishell called with argument");
	if (getenv("USER") == NULL)
		ms_error("no env");
	core = galloc(sizeof(t_core));
	core->env = galloc(sizeof(t_env));
	core->env->user_name = getenv("USER");
	core->env->hostname = getenv("NAME");
	core->env->paths = ft_split(getenv("PATH"), ':');
	core->ms_stdin = dup(STDIN_FILENO);
	core->ms_stdout = dup(STDOUT_FILENO);
	return (core);
}