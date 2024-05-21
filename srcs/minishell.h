/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/21 17:24:35 by hlibine          ###   ########.fr       */
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
# include <errno.h>
# include "../libs/extended_ft/srcs/extended_ft.h"

// Default Variables
# define DEF_COLOR "\033[35m"

# define QUOTES "\"\'"
# define REDIRECTS "<>|"
# define WHITESPACE " \n\t"

# define NOENVPATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

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

typedef struct s_envparam
{
	bool				base;
	char				*name;
	char				*value;
	struct s_envparam	*next;
	struct s_envparam	*prev;
}						t_envparam;

typedef struct s_env
{
	t_envparam	*rawenvs;
	bool		hasenv;
	char		*user;
	char		*hostname;
	char		**paths;
}	t_env;

typedef struct s_core
{
	int				argc;
	char			**argv;
	t_env			*env;
	char			*current_dir;
	char			*prompt;
	char			*line;
	t_token			*token;
	int				ms_stdin;
	int				ms_stdout;
}	t_core;

// functions
void		ms_error(char *in);
void		ms_printerror(char *in);
t_token		*ms_newtoken(char *content);
t_core		*init(int ac, char **av, char **env);
t_token		*ms_tokenlast(t_token *token);
void		ms_addtoken_back(t_core *core, t_token *new);
void		ms_tokensclear(t_token *token);
int			tokenizer(const char *input, t_core *core);
t_core		*minishell_loop(int ac, char **av, char **env);
void		addenvend(t_core *core, char *in, bool env);
t_envparam	*findenv(const char *name);
void		modifenv(t_envparam *env, const char *str);
t_core		*get_core(void);
void		init_envs(t_core *core, char **env);
void		init_noenv(t_core *core);
void		fill_core_env(t_core *core);
void		clear_envs(t_envparam *envs);

#endif