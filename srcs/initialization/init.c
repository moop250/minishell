/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/14 17:28:50 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_gethostname(t_core *core)
{
	t_envparam	*hostname;

	hostname = findenv(core, "NAME");
	if (!hostname)
		hostname = findenv(core, "HOSTNAME");
	if (!hostname)
		hostname = findenv(core, "LOGNAME");
	if (!hostname)
		return (NULL);
	return (ft_strdup(hostname->value));
}

static void	init_prompt(t_core *core)
{
	char	*tmp;
	tmp = ft_strjoin(core->prompt->color, core->env->user);
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
		addenvend(core, env[i], a, true);
	}
}

t_core	*init(int ac, char **av, char **env)
{
	t_core	*core;

	if (ac > 1)
		ms_error("minishell called with argument");
	if (!env)
		ms_error("no env");
	core = galloc(sizeof(t_core));
	core->env = galloc(sizeof(t_env));
	core->env->rawenvs = galloc(sizeof(t_envparam));
	(*core->env->rawenvs) = NULL;
	core->token = galloc(sizeof(t_token));
	(*core->token) = NULL;
	core->prompt = galloc(sizeof(t_prompt));
	init_envs(core, env);
	core->env->user = findenv(core,"USER")->value;
	core->env->paths = ft_split(findenv(core, "PATH")->value, ':');
	core->env->hostname = ms_gethostname(core);
	core->prompt->color = ft_strdup(DEF_COLOR);
	modifenv(findenv(core, "SHLVL"),
		ft_itoa(ft_atoi(findenv(core, "SHLVL")->value) + 1));
	init_prompt(core);
	return (core);
}