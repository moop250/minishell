/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/18 14:40:32 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

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
		tmp = ft_strjoin("minshell:\033[1;34m", findenv("PWD")->value);
		prompt = ft_strjoin(tmp, "\033[0m$ ");
		gfree(tmp);
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
		ms_error("readline error");
	addgarbage(tmp);
	gfree(prompt);
	return (tmp);
}

t_core	*minishell_loop(int ac, char **av, char **env)
{
	t_core		*core;
	t_pipeline	*tmp;
	t_pipe_fd	*pipeline_fd;
	int			i;
	int			a;

	while (true)
	{
		core = init(ac, av, env);
		core->line = ms_prompt(core);
		//temp exit
		if (ft_strcmp(core->line, "exit") == 0)
			break ;
		if (!tokenizer(ft_strtrim(core->line, WHITESPACE), core))
			continue ;
		parser(core, core->token);
		tmp = core->pipeline;
		a = -1;
		while (tmp)
		{
			ft_printf_fd(core->ms_stdout, "pipleine %i\n", ++a);
			i = -1;
			pipeline_fd = tmp->pipeline_in;
			while (pipeline_fd)
			{
				ft_printf_fd(core->ms_stdout, "file name: %s : heredoc %i\n", pipeline_fd->file_name, pipeline_fd->heredoc);
				pipeline_fd = pipeline_fd->next;
			}
			ft_printf_fd(core->ms_stdout, "cmd: %s\n", tmp->cmd);
			if (tmp->params)
				while (tmp->params[++i])
					ft_printf_fd(core->ms_stdout, "param: %s\n", tmp->params[i]);
			pipeline_fd = tmp->pipeline_out;
			while (pipeline_fd)
			{
				ft_printf_fd(core->ms_stdout, "file name: %s : heredoc %i\n", pipeline_fd->file_name, pipeline_fd->append);
				pipeline_fd = pipeline_fd->next;
			}
			tmp = tmp->next;
		}
		ms_pipelinesclear(&core->pipeline);
		printf("\n");
	}
	gfree(core->line);
	return (core);
}
