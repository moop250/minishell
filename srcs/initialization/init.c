/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 16:44:53 by hlibine          ###   ########.fr       */
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
	static t_core	*core;

	if (core)
		return (core);
	if (ac > 1)
		ms_error("minishell called with argument");
	core = galloc(sizeof(t_core));
	core->env = galloc(sizeof(t_env));
	core->env->rawenvs = galloc(sizeof(t_envparam));
	(*core->env->rawenvs) = NULL;
	core->token = galloc(sizeof(t_token));
	(*core->token) = NULL;
	core->prompt = galloc(sizeof(t_prompt));
	if (!env)
		ms_error("no env");
	init_envs(core, env);
	core->env->user = findenv("USER")->value;
	core->env->paths = ft_split(findenv("PATH")->value, ':');
	core->env->hostname = ms_gethostname(core);
	core->prompt->color = ft_strdup(DEF_COLOR);
	modifenv(findenv("SHLVL"),
		ft_itoa(ft_atoi(findenv("SHLVL")->value) + 1));
	init_prompt(core);
	core->ms_stdin = dup(STDIN_FILENO);
	core->ms_stdout = dup(STDOUT_FILENO);
	return (core);
}

t_core	*get_core(void)
{
	static t_core *core;

	if (!core)
		core = init(0, 0, 0);
	return (core);
}