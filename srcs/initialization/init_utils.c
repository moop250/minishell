/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:12:33 by pberset           #+#    #+#             */
/*   Updated: 2024/07/30 15:53:23 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_gethostname(void)
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
	char	*tmp;
	char	*str;

	core->env->hasenv = false;
	addenvend(core, "OLDPWD", false);
	addenvend(core, "SHLVL=1", true);
	core->env->paths = ft_split(NOENVPATH, ':');
	tmp = ms_getcwd();
	str = ft_strjoin("PWD=", tmp);
	addenvend(core, str, true);
	addenvend(core, "_=", true);
	gfree(tmp);
	gfree(str);
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
	core->prompt = NULL;
	if (core->env->hasenv == true)
	{
		core->env->user = findenv("USER")->value;
		core->env->home = findenv("HOME")->value;
		core->env->hostname = ms_gethostname();
		if (!findenv("SHLVL"))
			addenvend(core, ft_strdup("SHLVL=1"), true);
		else
			modifenv(findenv("SHLVL"),
				ft_itoa(ft_atoi(findenv("SHLVL")->value) + 1));
	}
	else
		core->env->user = core->argv[0];
}

void	clear_envs(t_envparam *envs)
{
	t_envparam	*temp;

	if (!envs)
		return ;
	while (envs)
	{
		temp = envs->next;
		if (!envs)
			return ;
		gfree(envs->name);
		gfree(envs->value);
		gfree(envs);
		envs = temp;
	}
	envs = NULL;
	return ;
}
