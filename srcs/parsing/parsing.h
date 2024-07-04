/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:24:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/04 16:22:59 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include "../lexing/lexing.h"

# define SEPERATOR "+-=;'\"~/?$.,<>]{} \n\t"

char		*parse_envvars(const char *in);
t_pipeline	*ms_addpipeline_back(t_core *core);
void		ms_pipelinesclear(t_pipeline **pipeline);
t_pipe_fd	*ms_addpipe_fd_back(t_pipe_fd **pipe_fd);
void		ms_freepipefd(t_pipe_fd **pipe_fd);
void		setdelimiter(t_pipeline **pipe, t_token **token, int status);
char		*strwrk(size_t pos[3], const char *in, char	*out);
size_t		quotewrk(const char *in, t_list **list);
size_t		treat_dollar(const char *in, t_list **list, size_t pos);
size_t		treat_text(const char *in, t_list **list, size_t pos[2], int mode);

#endif
