/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:39 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/03 20:28:26 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static char	*dbl_quotes(const char *in)
{
	size_t	pos[3];
	char	*tmp[2];
	char	*out;

	pos[0] = 0;
	pos[1] = 1;
	out = ft_strdup("");
	while (in[++pos[0]] != '"')
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
	}
	tmp[0] = ft_substr(in, pos[1], pos[0] - pos[1]);
	tmp[1] = ft_strjoin(out, tmp[0]);
	return (gfree(out), gfree(tmp[0]), tmp[1]);
}

static char	*sgl_quotes(const char *in)
{
	size_t	tmp;
	char	*out;

	tmp = 0;
	while (in[++tmp] != '\'')
		;
	out = ft_substr(in, 1, tmp - 1);
	return (out);
}

static char	*quotewrk(const char *in)
{
	char	*out;

	if (in[0] == '"')
		out = dbl_quotes(in);
	else
		out = sgl_quotes(in);
	return (out);
}

static int	treat_dollar(const char *in, t_list *list, int pos)
{
	int		out;
	char	*tmp;

	out = 0;
	while (in[++out] && !ft_strchr(SEPERATOR, in[out]))
		;
	tmp = ft_substr(in, 1, out);
	printf("%s¦\n", tmp);
	ft_lstadd_back(&list, ft_lstnew(findenvvalue(tmp)));
	gfree(tmp);
	return (out + pos);
}

static char	*recombine(t_list *list)
{
	t_list	*tmp;
	char	*str;
	char	*out;

	out = ft_strdup("");
	tmp = list;
	while (tmp)
	{
		str = ft_strjoin(out, tmp->content);
		gfree(out);
		out = str;
		tmp = tmp->next;
	}
	ft_lstclear(&list);
	return (out);
}

/*
	pos[0] = position for in
	pos[1] = start of current array section
*/

char	*parse_envvars(const char *in)
{
	t_list	*list;
	int		pos[2];
	char	tmp;

	list = NULL;
	pos[0] = 0;
	pos[1] = 0;
	while (in[pos[0]])
	{
		if (in[pos[0]] == '\'' || in[pos[0]] == '"')
		{
			tmp = in[pos[0]];
			ft_lstadd_back(&list, ft_lstnew(quotewrk(in + pos[0])));
			while (in[++pos[0]] && in[pos[0]] != tmp)
				;
			++pos[0];
			pos[1] = pos[0];
		}
		else if (in[pos[0]] == '$')
		{
			pos[0] = treat_dollar(in + pos[0], list, pos[0]);
			pos[1] = pos[0];
		}
		else
		{
			while (in[pos[0]] != '"' && in[pos[0]] != '\''
				&& in[pos[0]] != '$' && in[pos[0]])
			++pos[0];
			ft_lstadd_back(&list, ft_lstnew(ft_substr(in, pos[1], pos[0] - pos[1])));
		}
	}
	return (recombine(list));
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
