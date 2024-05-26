/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:22:34 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/26 13:07:09 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
//# include <sys/syslimits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
//# include <strings.h>
//# include <cstdlib.h>
# include "../headers/colors.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef DEBUG_ACTIVE
#  define DEBUG_ACTIVE 0
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// <ctype.h>
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

// <string.h>
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);

char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);

// <stdlib.h>
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s);

/*
**
**      Funciones extra
**
*/

char				*ft_itoa(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set); //falla
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
**
**      Listas
**
*/

t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);

/*
**
**      GNL
**
*/

char				*get_next_line(int fd);
char				*get_next_line_no_nl(int fd);

/*
**
**      Printf
**
*/

int					ft_printf(const char *str, ...);

void				ft_putcharcnt(char c, int *count);
void				ft_putstrcnt(char *s, int *count);
void				ft_putnbrcnt(long n, int *count);
void				ft_puthexcnt(unsigned long int n, int ucase, int prefix,
						int *count);

/*
**
**      Mis funciones
**
*/

char				*ft_strjoinfree(char *s1, char *s2);
char				*ft_strjoinfree1(char *s1, char *s2);
char				*ft_strjoinfree2(char *s1, char *s2);
char				*ft_strjoinglue(char const *glue, ...);
char				*ft_strjoinmulti(char const *first, ...);

int					ft_arrayfree(char **array);
int					array_len(char **array);
void				ft_perror(char *str, int status, ...);
int					ft_printf_debug(char const *format, int debug, ...);

int					ft_isspace(int c);

long				ft_atol(const char *str);

int					ft_strcmp(const char *s1, const char *s2);

#endif