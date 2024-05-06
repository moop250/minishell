/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/06 15:40:45 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(t_core *core)
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
	core->token = galloc(sizeof(t_token));
	(*core->token) = NULL;
	core->prompt = galloc(sizeof(t_prompt));
	core->prompt->color = ft_strdup("\033[35m");
	init_prompt(core);
	return (core);
}