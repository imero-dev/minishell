/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:26:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/26 03:07:56 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/src/libft.h"

typedef struct 	s_commandlist
{
	char 					*command;
	char					**args;
	struct s_commandlist 	*next;
}				t_commandlist;

typedef struct 	s_data
{
    char            *line;
    char            *last_line;
    t_commandlist	*commandlist;
}				t_data;

// dirs.c
int com_pwd(void);
int com_cd(char *arg);

#endif