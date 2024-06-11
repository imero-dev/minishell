/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:26:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/11 18:21:38 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include "../libft/src/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_commandlist
{
	char					*command;
	char					**args;
	struct s_commandlist	*next;
}							t_commandlist;

typedef struct 	s_envlist
{
	char 					*name;
	char					*value;
	bool					export;
	struct s_envlist 		*next;
}							t_envlist;

typedef struct s_data
{
	char					*line;
	char					*last_line;
	char					*prompt;
	t_commandlist			*commandlist;
	int						last_exit_status;
}							t_data;

// dirs.c
int							com_pwd(void);
int							com_cd(char *arg);
char						*get_actual_dir(void);

// echo.c
void						ft_echo(char **args);

// enviroments.c
char 						*env_name(char *env);
char 						*env_value(char *env);
t_envlist 					*new_env(char *name, char *value, bool export);
void 						add_env(t_envlist **lst, t_envlist *new);
t_envlist 					*env_initializer(char ** env);
void 						env_writer(t_envlist * env);
t_envlist 					*unset(t_envlist *env, char **words);
t_envlist					*export(t_envlist	*env_vars, char **words);
void 						free_envlist(t_envlist *head);
// syntax_spliter.c
char						**syntax_spliter(const char *str);

// signals.c
void						handle_sigint(int sig);
void						handle_sigquit(int sig);
void						exit_shell(char *msg, int status);

// debug.c
void						print_words(char **words);
void						execute_on_bash(char *command);

// main.c
t_data						*get_data(void);
void						garbage_collector(void);

#endif
