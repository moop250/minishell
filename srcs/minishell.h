/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/30 13:42:59 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "../libs/extended_ft/srcs/extended_ft.h"

// enums
typedef enum e_token_type
{
	token_cmd,
	token_var,
	tokeb_pipe,
	token_stdin,
	token_stdout,
}			t_token_type;

// structs
typedef struct s_token
{
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
}	t_token;

typedef struct s_env
{
	char	*user_name;
	char	*hostname;
	char	**paths;
}	t_env;

typedef struct s_core
{
	struct s_env	*env;
	char			*current_dir;
	char			*prompt;
	int				ms_stdin;
	int				ms_stdout;
}	t_core;

// functions
void	ms_error(char *in);
void	ms_printerror(char *in);
t_core	*init(int ac, char **env);

#endif