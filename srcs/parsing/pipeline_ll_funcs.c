/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_ll_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:02:01 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/29 13:01:47 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_pipeline	*newpipe(void)
{
	t_pipeline	*node;

	node = galloc(sizeof(t_pipeline));
	if (!node)
		return (NULL);
	node->params = NULL;
	node->param_count = 0;
	node->heredoc = false;
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

t_pipeline	*ms_addpipeline_back(t_core *core)
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
	return (new);
}

static void	ms_pipelinedelone(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->params)
	{
		ft_2dfree((void **)pipeline->params);
		if (pipeline->pipeline_out)
			ms_freepipefd(&pipeline->pipeline_out);
		if (pipeline->pipeline_in)
			ms_freepipefd(&pipeline->pipeline_in);
		gfree(pipeline);
	}
}

void	ms_pipelinesclear(t_pipeline **pipeline)
{
	t_pipeline	*next;
	t_pipeline	*current;

	if (!pipeline || !*pipeline)
		return ;
	current = *pipeline;
	while (current)
	{
		next = current->next;
		ms_pipelinedelone(current);
		current = next;
	}
	*pipeline = NULL;
	return ;
}
