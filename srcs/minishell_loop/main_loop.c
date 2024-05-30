/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/30 16:59:18 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *make_prompt(t_core *core)
{
	char	*prompt = core->prompt;
	char	*tmp;

	if (prompt != NULL)
		gfree(prompt);
	if (core->env->hasenv == false)
		prompt = ft_strjoin(&core->argv[0][2], "$ ");
	else
	{
		tmp = ft_strjoin("minshell:\033[1;34m", findenv("PWD")->value);
		prompt = ft_strjoin(tmp, "\033[0m$ ");
		gfree(tmp);
	}
	return (prompt);
}

static char *ms_prompt(t_core *core)
{
	char	*tmp;
	char	*prompt;

	prompt = make_prompt(core);
	tmp = readline(prompt);
	if (!tmp)
		ms_error("readline error");
	addgarbage(tmp);
	gfree(prompt);
	return (tmp);
}

t_core	*minishell_loop(int ac, char **av, char **env)
{
	t_core	*core;
	t_token	*tmp;

	while (true)
	{
		core = init(ac, av, env);
		core->line = ms_prompt(core);
		//temp exit
		if(ft_strcmp(core->line, "exit") == 0)
			break ;
		if (!tokenizer(ft_strtrim(core->line, WHITESPACE), core))
			continue ;
		tmp = core->token;
		while (tmp)
		{
			ft_printf_fd(core->ms_stdout, "--->%s", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		ms_tokensclear(&core->token);
		
	}
	gfree(core->line);
	return (core);
}
