/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ll_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:02:01 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/30 19:46:02 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_pipeline	*newpipe(void)
{
	t_pipeline	*node;

	node = galloc(sizeof(t_pipeline));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->params = NULL;
	node->heredoc = NULL;
	node->pipeline_in = NULL;
	node->pipeline_out = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_pipeline	*ms_pipelinelast(t_pipeline *pipeline)
{
	while (pipeline)
	{
		if (pipeline->next == NULL)
			return (pipeline);
		pipeline = pipeline->next;
	}
	return (pipeline);
}

void	ms_addpipeline_back(t_core *core)
{
	t_pipeline	*pipeline;
	t_pipeline	*tmp;
	t_pipeline	*new;

	new = newpipe();
	pipeline = core->pipeline;
	if (!core->pipeline)
		core->pipeline = new;
	else
	{
		tmp = ms_pipelinelast(pipeline);
		new->prev = tmp;
		tmp->next = new;
	}
}

static void	ms_pipelinedelone(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	gfree(pipeline->cmd);
	i = -1;
	while (pipeline->params[++i])
		gfree(pipeline->params[i]);
	if (pipeline->pipeline_out)
		ms_freepipeout(pipeline->pipeline_out);
	gfree(pipeline);
	return ;
}

void	ms_pipelinesclear(t_pipeline **pipeline)
{
	t_pipeline	*temp;

	if (!pipeline)
		return ;
	while (*pipeline)
	{
		temp = (*pipeline)->next;
		ms_pipelinedelone(*pipeline);
		*pipeline = temp;
	}
	*pipeline = NULL;
	return ;
}