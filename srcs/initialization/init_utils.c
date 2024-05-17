/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:00:30 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/17 14:40:48 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_gethostname(t_core *core)
{
	t_envparam	*hostname;

	hostname = findenv("NAME");
	if (!hostname)
		hostname = findenv("HOSTNAME");
	if (!hostname)
		hostname = findenv("LOGNAME");
	if (!hostname)
		return (NULL);
	return (ft_strdup(hostname->value));
}

void	init_noenv(t_core *core)
{
	core->env->hasenv = false;
	addenvend(core, "SHLVL=1", true);
	core->env->paths = ft_split(NOENVPATH, ':');
}

void	init_envs(t_core *core, char **env)
{
	int	i;
	int	a;

	i = -1;
	core->env->hasenv = true;
	while (env[++i])
	{
		a = -1;
		while (env[i][++a] != '=')
			;
		addenvend(core, env[i], true);
	}
	core->env->paths = ft_split(findenv("PATH")->value, ':');
}

void	fill_core_env(t_core *core)
{
	if (core->env->hasenv == true)
	{
		core->env->user = findenv("USER")->value;
		core->env->hostname = ms_gethostname(core);
		modifenv(findenv("SHLVL"),
			ft_itoa(ft_atoi(findenv("SHLVL")->value) + 1));
	}
	else
	{
		core->env->user = core->argv[0];
	}
}
