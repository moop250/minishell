/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/06 17:17:49 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/extended_ft/srcs/extended_ft.h"

// Default Variables
# define QUOTES "\"\'"
# define REDIRECTS "<>|"
# define WHITESPACE " \n\t"

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

typedef struct s_prompt
{
	char	*color;
	char	*prompt;
}			t_prompt;

typedef struct s_core
{
	t_env			*env;
	char			*current_dir;
	t_prompt		*prompt;
	char			*line;
	t_token			**token;
	int				ms_stdin;
	int				ms_stdout;
}	t_core;

// functions
void	ms_error(char *in);
void	ms_printerror(char *in);
t_token	*ms_newtoken(char *content);
t_core	*init(int ac, char **env);
t_token	*ms_tokenlast(t_token *token);
void	ms_addtoken_back(t_core *core, t_token *new);
void	ms_tokensclear(t_token **token);
char	**tokenizer(const char *input, t_core *core);
void	minishell_loop(t_core *core);

#endif