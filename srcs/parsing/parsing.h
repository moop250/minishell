/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:24:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/19 14:35:13 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include "../lexing/lexing.h"

# define SEPERATOR "+-=;'\"~/?$.<>]{} \n\t"

char		*parse_quotes(char *in);
t_pipeline	*ms_addpipeline_back(t_core *core);
void		ms_pipelinesclear(t_pipeline **pipeline);
t_pipe_fd	*ms_addpipe_fd_back(t_pipe_fd **pipe_fd);
void		ms_freepipefd(t_pipe_fd **pipe_fd);
void		setdelimiter(t_pipeline **pipe, t_token **token, int status);

#endif
