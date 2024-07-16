/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/16 14:29:26 by hlibine          ###   LAUSANNE.ch       */
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

static void	ms_update(t_core *core)
{
	gfree(core->env->cwd);
	core->env->cwd = ms_getcwd();
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
	core->env->envp = env;
	core->env->rawenvs = NULL;
	core->env->cwd = ms_getcwd();
	core->token = NULL;
	core->argc = ac;
	core->argv = av;
	if (!env[0])
		init_noenv(core);
	else
		init_envs(core, env);
	fill_core_env(core);
	core->ms_stdin = dup(STDIN_FILENO);
	core->ms_stdout = dup(STDOUT_FILENO);
	core->pipeline = NULL;
	core->exit_status = 0;
	return (core);
}

t_core	*get_core(void)
{
	static t_core	*core;

	if (!core)
		core = init(0, 0, 0);
	return (core);
}
