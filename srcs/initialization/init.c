/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/29 10:23:51 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_getcwd(void)
{
	char	*result;
	char	path[PATH_MAX];

	result = NULL;
	result = getcwd(result, sizeof(path));
	if (!result)
		ms_error("getcwd error");
	addgarbage(result);
	return (result);
}

void	ms_update(t_core *core)
{
	t_envparam	*tmp;
	int			i;
	char		*temp;

	i = -1;
	gfree(core->env->cwd);
	core->env->cwd = ms_getcwd();
	ft_2dfree((void **)core->env->paths);
	core->env->paths = ms_get_env_paths();
	ft_2dfree((void **)core->env->envp);
	tmp = core->env->rawenvs;
	while (++i, tmp)
		tmp = tmp->next;
	core->env->envp = galloc((i + 1) * sizeof(char *));
	core->env->envp[i] = NULL;
	i = -1;
	tmp = core->env->rawenvs;
	while (++i, tmp)
	{
		temp = ft_strjoin(tmp->name, "=");
		core->env->envp[i] = ft_strjoin(temp, tmp->value);
		gfree(temp);
		tmp = tmp->next;
	}
}

static void	set_env(t_core *core, char **env)
{
	int	i;

	i = -1;
	core->env = galloc(sizeof(t_env));
	while (env[++i])
		;
	core->env->envp = galloc((i + 1) * sizeof(char *));
	core->env->envp[i] = NULL;
	i = -1;
	while (env[++i])
		core->env->envp[i] = ft_strdup(env[i]);
	core->env->rawenvs = NULL;
	core->env->cwd = ms_getcwd();
}

t_core	*init(int ac, char **av, char **env)
{
	static t_core	*core = NULL;
	char			*tmp;

	if (core)
		return (core);
	if (ac > 1)
		ms_error("minishell called with argument");
	core = galloc(sizeof(t_core));
	core->token = NULL;
	set_env(core, env);
	core->argc = ac;
	core->argv = av;
	if (!core->env->envp[0])
		init_noenv(core);
	else
		init_envs(core, core->env->envp);
	fill_core_env(core);
	core->pipeline = NULL;
	core->exit_status = 0;
	if (!findenv("PWD"))
	{
		addenvend(core, tmp = ft_strjoin("PWD=", ms_getcwd()), true);
		gfree(tmp);
	}
	return (core);
}

t_core	*get_core(void)
{
	static t_core	*core;

	if (!core)
		core = init(0, 0, 0);
	return (core);
}
