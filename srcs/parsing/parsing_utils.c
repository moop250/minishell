/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/02 14:01:48 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static char	*ms_seperate_env(const char *in)
{
	char	*out;
	char	*tmp;
	size_t	i;

	i = 1;
	while (!ft_strchr(SEPERATOR, in[i]))
		++i;
	tmp = ft_substr(in, 1, i - 1);
	out = findenvvalue(tmp);
	gfree(tmp);
	return (out);
}

static char	*strwrk(size_t pos[3], const char *in, char	*out)
{
	char	*tmp[2];

	tmp[0] = ft_substr(in, pos[1], pos[2] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	out = tmp[1];
	tmp[0] = ms_seperate_env(in + pos[2]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	gfree(out);
	gfree(tmp[0]);
	out = tmp[1];
	return (out);
}

/*
	pos[0] = position for in
	pos[1] = start of current array section
	pos[2] = end of curent array section
*/

char	*parse_envvars(const char *in, int mode)
{
	char	*out;
	size_t	pos[3];
	char	*tmp[2];

	pos[0] = mode - 1;
	pos[1] = mode;
	out = ft_strdup("");
	while (in[++pos[0] + mode])
	{
		if (in[pos[0]] == '$')
		{
			pos[2] = pos[0];
			out = strwrk(pos, in, out);
			while (in[++pos[0]] && !ft_strchr(SEPERATOR, in[pos[0]]))
				;
			pos[1] = pos[0];
			if (in[pos[0]] == '$')
				--pos[0];
		}
		if (in[pos[1]] == '"' || !in[pos[1]])
			return (out);
	}
	tmp[0] = ft_substr(in, pos[1], pos[0] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	return (gfree(out), gfree(tmp[0]), tmp[1]);
}

void	setdelimiter(t_pipeline **pipe, t_token **token, int status)
{
	t_pipe_fd	*tmp;

	if (status == 1)
	{
		tmp = ms_addpipe_fd_back(&(*pipe)->pipeline_in);
		if ((*token)->content[1])
			tmp->heredoc = true;
	}
	else
	{
		tmp = ms_addpipe_fd_back(&(*pipe)->pipeline_out);
		if ((*token)->content[1])
			tmp->append = true;
	}
	tmp->file_name = ft_strdup((*token)->next->content);
	(*token) = (*token)->next;
}
