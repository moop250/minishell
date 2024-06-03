/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_fd_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:05:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/03 16:00:07 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_pipe_fd	*newpipe(void)
{
	t_pipe_fd	*node;

	node = galloc(sizeof(t_pipe_fd));
	if (!node)
		return (NULL);
	node->append = false;
	node->heredoc = false;
	node->fd = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_pipe_fd	*ms_pipe_fdlast(t_pipe_fd *pipe_fd)
{
	while (pipe_fd)
	{
		if (pipe_fd->next == NULL)
			return (pipe_fd);
		pipe_fd = pipe_fd->next;
	}
	return (pipe_fd);
}

t_pipe_fd	*ms_addpipe_fd_back(t_pipe_fd *pipe_fd)
{
	t_pipe_fd	*tmp;
	t_pipe_fd	*new;

	new = newpipe();
	if (!pipe_fd)
		pipe_fd = new;
	else
	{
		tmp = ms_pipe_fdlast(pipe_fd);
		new->prev = tmp;
		tmp->next = new;
	}
	return (new);
}

static void	ms_pipe_fddelone(t_pipe_fd *pipe_fd)
{
	int	i;

	if (!pipe_fd)
		return ;
	gfree(pipe_fd->file_name);
	close(pipe_fd->fd);
	gfree(pipe_fd);
	return ;
}

void	ms_pipefd_clear(t_pipe_fd **pipe_fd)
{
	t_pipe_fd	*temp;

	if (!pipe_fd)
		return ;
	while (*pipe_fd)
	{
		temp = (*pipe_fd)->next;
		ms_pipe_fddelone(*pipe_fd);
		*pipe_fd = temp;
	}
	*pipe_fd = NULL;
	return ;
}