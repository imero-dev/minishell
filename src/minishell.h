/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:26:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/19 03:31:57 by ivromero         ###   ########.fr       */
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
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


typedef struct s_commandlist
{
	int						pipefd[2];
	int 					fd_in;
	int 					fd_out;
	char					*command;
	char					**args;
	char 					**redirects;
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
	int						last_exit_status;
	//	int						pipes_num;
	t_commandlist			*commandlist;
	t_envlist				*env_vars;
}							t_data;

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

// signals.c
void						handle_sigint(int sig);
void						handle_sigquit(int sig);
void						exit_shell(char *msg, int status);

// redirections.c
int							input_redirections(char **words);
void 						ft_heredoc(char *eof);
int 						output_redirections(char **words);

// debug.c
void						print_words(char **words);
void						execute_on_bash(char *command);

// minishell.c
t_data						*get_data(void);
void						garbage_collector(void);

// command.c
int							add_command(char **args);
void						free_commandlist(t_commandlist **commandlist);
int							exec_command(t_commandlist *command);
int							run_commands(void);

#endif
