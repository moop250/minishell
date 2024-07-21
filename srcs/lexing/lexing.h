/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:34:26 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/21 11:50:52 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../minishell.h"

t_token	*ms_newtoken(char *content);
t_token	*ms_tokenlast(t_token *token);
void	ms_addtoken_back(t_core *core, t_token *new);
void	ms_tokensclear(t_token *token);

#endif
