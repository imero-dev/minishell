/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:26:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/27 18:19:22 by ivromero         ###   ########.fr       */
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

typedef struct s_data
{
	char					*line;
	char					*last_line;
	t_commandlist			*commandlist;
}							t_data;

// dirs.c
int							com_pwd(void);
int							com_cd(char *arg);
char						*get_actual_dir(void);

// echo.c
void						ft_echo(char **args);

// syntax_spliter.c
char						**syntax_spliter(const char *str);

// signals.c
void						handle_sigint(int sig);
void						handle_sigquit(int sig);
void						exit_shell(char *msg);

// debug.c
void						print_words(char **words);
void						execute_on_bash(char *command);

// main.c
t_data						*get_data(void);
void						garbage_collector(void);

#endif