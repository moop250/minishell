/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/24 17:37:20 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"
#include "../builtins/builtins.h"

char	*make_prompt(t_core *core)
{
	char	*prompt;
	char	*tmp;

	prompt = core->prompt;
	if (prompt != NULL)
		gfree(prompt);
	if (core->env->hasenv == false)
		prompt = ft_strjoin(&core->argv[0][2], "$ ");
	else
	{
		tmp = ft_strjoin("minisHELLdivers:", findenv("PWD")->value);
		prompt = ft_strjoin(tmp, "$ ");
		free(tmp);
	}
	return (prompt);
}

static char	*ms_prompt(t_core *core)
{
	char	*tmp;
	char	*prompt;

	prompt = make_prompt(core);
	tmp = readline(prompt);
	if (!tmp)
	{
		ft_printf_fd(1, "exit\n");
		gfree(prompt);
		return (NULL);
	}
	addgarbage(tmp);
	gfree(prompt);
	return (tmp);
}

t_core	*minishell_loop(int ac, char **av, char **env)
{
	t_core	*core;
	t_core	*temp;

	while (true)
	{
		core = init(ac, av, env);
		core->line = ms_prompt(core);
		if (core->line == NULL)
			break ;
		add_history(core->line);
		if (tokenizer(ft_strtrim(core->line, WHITESPACE), core) < 0)
			continue ;
		parser(core, core->token);
		if (core->token_count > 0)
		{
			temp = core;
			core->exit_status = execute(temp);
		}
		ms_pipelinesclear(&core->pipeline);
	}
	rl_clear_history();
	gfree(core->line);
	return (core);
}
