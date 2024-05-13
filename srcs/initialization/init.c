/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/13 17:02:38 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_prompt(t_core *core)
{
	char	*tmp;
	tmp = ft_strjoin(core->prompt->color, core->env->user_name);
	core->prompt->prompt = tmp;
	tmp = ft_strjoin(core->prompt->prompt, "@");
	gfree(core->prompt->prompt);
	core->prompt->prompt = tmp;
	tmp = ft_strjoin(core->prompt->prompt, core->env->hostname);
	gfree(core->prompt->prompt);
	core->prompt->prompt = tmp;
	tmp = ft_strjoin(core->prompt->prompt, ": \033[0m");
	gfree(core->prompt->prompt);
	core->prompt->prompt = tmp;
}

static void	init_envs(t_core *core, char **env)
{
	int	i;
	int	a;

	i = -1;
	while (env[++i])
	{
		a = -1;
		while (env[i][++a] != '=')
			;
		addenvend(env[i], a, true);
	}
}

t_core	*init(int ac, char **av, char **env)
{
	t_core	*core;
	int		i;

	if (ac > 1)
		ms_error("minishell called with argument");
	if (!env)
		ms_error("no env");
	init_envs(core, env);
	//set things like the name / hostame for the prompt
	return (core);
}