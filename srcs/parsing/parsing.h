/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:24:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/07 15:04:32 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include "../lexing/lexing.h"

# define SEPERATOR "+-=;'~/?$.<>]{} \n\t"

t_pipeline	*ms_addpipeline_back(t_core *core);
void		ms_pipelinesclear(t_pipeline **pipeline);
t_pipe_fd	*ms_addpipe_fd_back(t_pipe_fd *pipe_fd);

#endif
