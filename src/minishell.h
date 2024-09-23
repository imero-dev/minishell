/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:26:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/24 01:14:26 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define FD_IN 0
# define FD_OUT 1

# include "../libft/src/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# include <bits/termios-c_lflag.h>

// FIXME Deberia haber una global para el status de salida de los comandos pero lo hacemos con el singleton get_data()->last_exit_status

typedef struct s_commandlist
{
	int						pipefd[2];
	int						fd_in;
	int						fd_out;
	int						syntax_error;
	char					*command;
	char					**tokens;
	char					**args;
	char					**redirects;
	struct s_commandlist	*next;
}							t_commandlist;

typedef struct s_envlist
{
	char					*name;
	char					*value;
	bool					export;
	struct s_envlist		*next;
}							t_envlist;

typedef struct s_data
{
	char					*line;
	char					*last_line;
	char					*prompt;
	char 					**orders; // ordenes entre pipes
	int						last_exit_status;
	bool					runing_commands;
	//	int						pipes_num;
	t_commandlist			*commandlist;
	t_envlist				*env_vars;
}							t_data;

typedef struct s_spliterdata
{
	char					**tokens;
	char					*current_token;
	size_t					tokens_size;
	size_t					token_length;
	size_t					token_capacity;
	size_t					len;
	size_t					i;
	bool					in_single_quote;
	bool					in_double_quote;
	bool					expand_env;
	bool 					quoted_token;
}							t_spliterdata;

// dirs.c
int							com_pwd(void);
int							com_cd(char **args);
char						*get_actual_dir(void);

// echo.c
int							com_echo(char **args);

// exit.c
void						com_exit(char **args);

// enviroments.c
int							add_env(t_envlist **lst, t_envlist *new);
int							env_writer(t_envlist *env);
int							unset(t_envlist *env, char **words);
int							export(t_envlist *env_vars, char **words);
int							save_var(t_envlist *env_vars, char **words);

char						*get_name(char *env);
char						*get_value(char *env);
t_envlist					*new_env(char *name, char *value, bool export);
t_envlist					*env_initializer(char **env);
void						free_envlist(t_envlist *head);
char						*env_get(char *name);

// syntax_spliter.c
char						**syntax_spliter(const char *str);

// syntax_spliter_utils.c
int							initialize_data(t_spliterdata *data,
								const char *str);
char						**ft_add_to_array(char **tokens, size_t *size,
								char *new_token);
bool						check_unbalanced_quotes(t_spliterdata *data);

// syntax_classify_tokens.c
void						classify_tokens(t_commandlist *command);

// syntax_expand_env.c
void						expand_env(char **token);

// signals.c
void						handle_sigint(int sig);
void						handle_sigquit(int sig);
void						exit_shell(char *msg, int status);

// redirections.c
int							input_redirections(char **words);
void						ft_heredoc(char *eof);
int							output_redirections(char **words);

// minishell.c
t_data						*get_data(void);
void						garbage_collector(void);

// command.c
int							add_command(char **tokens);
void						free_commandlist(t_commandlist **commandlist);
int							exec_command(t_commandlist *command);
int							run_commands(void);

#endif
