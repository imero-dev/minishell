# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 13:25:53 by ivromero          #+#    #+#              #
#    Updated: 2024/05/26 02:12:04 by ivromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
NAME_DEBUG = libft_debug.a
NAME_VALGR 	= libft_valgr.a

SRC_NAME = \
ft_atoi.c		ft_isdigit.c	ft_memmove.c	ft_split.c		ft_strlcpy.c	ft_strrchr.c \
ft_bzero.c		ft_isprint.c	ft_memset.c		ft_strchr.c		ft_strlen.c		ft_substr.c \
ft_calloc.c		ft_itoa.c		ft_putchar_fd.c	ft_strdup.c		ft_strmapi.c	ft_tolower.c \
ft_isalnum.c	ft_memcmp.c		ft_putendl_fd.c	ft_striteri.c	ft_strncmp.c	ft_toupper.c \
ft_isalpha.c	ft_memcpy.c		ft_putnbr_fd.c	ft_strjoin.c	ft_strnstr.c \
ft_isascii.c	ft_memchr.c		ft_putstr_fd.c	ft_strlcat.c	ft_strtrim.c \
ft_lstnew.c		ft_lstadd_front.c ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c\
ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c	  ft_lstmap.c \
get_next_line.c	ft_printf.c		ft_printf_utils.c \
ft_arrayfree.c	ft_perror.c		ft_isspace.c	ft_strjoin_ext.c \
ft_arraylen.c	ft_printf_debug.c 

OBJ_NAME	= $(SRC_NAME:.c=.o)

SRC_PATH	= ./src/
OBJ_PATH	= ./obj/
OBJDBG_PATH	= ./obj_debug/
OBJVLG_PATH	= ./obj_valgr/

SRC			= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJS_DEBUG	= $(addprefix $(OBJDBG_PATH), $(OBJ_NAME))
OBJS_VALGR	= $(addprefix $(OBJVLG_PATH), $(OBJ_NAME))

CC		= cc
RM		= rm -f
AR		= ar rcs

CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic
DEBUG_FLAGS = -g3 -fsanitize=address -D DEBUG=2
VALGRIND_FLAGS = -g

RED			= \033[0;31m
ORANGE		= \033[0;33m
GREEN		= \033[0;32m
BLUE		= \e[1;34m\e[4m
NC			= \033[0m

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH)
		@echo "\e[u🟧\e[s"
		$(CC) $(CFLAGS) -o $@ -c $<
#		@echo -n 🟧

$(OBJDBG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJDBG_PATH)
		@$(CC) $(DEBUG_FLAGS) $(CFLAGS) -o $@ -c $<
		@echo -n 🟧

$(OBJVLG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJVLG_PATH)
		@$(CC) $(VALGRIND_FLAGS) $(CFLAGS) -o $@ -c $<
		@echo -n 🟧


all:	init 
		@make $(NAME) 

$(NAME): $(OBJS)
		@echo
		@echo "$(ORANGE)Linking:$(NC) $@"
		$(AR) $(NAME) $(OBJS)
		@echo "$(GREEN)Finished:$(NC) $@"
#		@make info
		
init:
		@echo "$(BLUE)Building $(NAME):$(NC)"
		@echo -n "⬛\e[s"
		@for i in $(OBJS); do \
			echo -n "⬛"; \
		done
		@echo "⬛"

clean:
		@$(RM) $(OBJS) $(OBJSBONUS) $(OBJS_DEBUG) $(OBJS_VALGR)
		@$(RM) -rf $(OBJ_PATH) $(OBJDBG_PATH) $(OBJVLG_PATH)
		@echo "$(GREEN)clean done:$(NC) $(NAME)"

fclean:	clean
		@$(RM) $(NAME) $(NAME_DEBUG) $(NAME_VALGR)
		@echo "$(GREEN)fclean done:$(NC) $(NAME)"

re:		fclean all

.PHONY : all clean fclean re info

debug:	$(NAME_DEBUG)

$(NAME_DEBUG): $(OBJS_DEBUG)
		@echo "flags: $(DEBUG_FLAGS)"
		@echo "\nLinking: $@"
		$(AR) $(NAME_DEBUG) $(OBJS_DEBUG)
		@echo "$(GREEN)Compilación terminada:$(NC) $@"

valgrind: $(NAME_VALGR)

$(NAME_VALGR): $(OBJS_VALGR)
		@echo "flags: $(VALGRIND_FLAGS)"
		@echo "\nLinking: $@"
		@$(AR) $(NAME_VALGR) $(OBJS_VALGR)
		@echo "$(GREEN)Compilación terminada:$(NC) $@"

info:
		@echo "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜"
		@echo "⬜                                                                ⬜"
		@echo "⬜      LIBFT sin {llaves} AKA tiny_libft                         ⬜"
		@echo "⬜                                                                ⬜"
		@echo "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜"
		@echo  
		@echo "Solo con las {} de las funciones 😳."
		@echo "Tratando de minimizar las funciones."
		@echo "Admito que en momentos me he visto en la tesitura de elegir entre optimizar código y optimizar tiempo de computo pero he mantenido un equilibrio. Se podía comprimir mas..."
		@echo "En el tester que he hecho un benchmark contra la función original para comprobar si era tan rápida. (Con strlen me ha ganado la máquina. El resto - o + empate.)"
		@echo "Con instrucciones como:"
		@echo "-------------------------------------------------------------------"
		@echo "while (nbr)\n	nbr /= 10 + (int)(0 * ++len);"
		@echo "-------------------------------------------------------------------"
		@echo "int	ft_tolower(int c)\n{\n	return (c + 32 * (c >= 'A' && c <= 'Z'));\n}"
		@echo "-------------------------------------------------------------------"
		@echo "if (n == -2147483648)\n		return (ft_putstr_fd("-2147483648", fd));"
		@echo "-------------------------------------------------------------------"
		@echo "if (!node)\n	return (ft_lstclear(new_list, del), del(content), NULL);"
		@echo "-------------------------------------------------------------------"
		@echo ""
		@echo ""
		 
		@echo "          ⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜"
		@echo "          ⬜⬜⬜⬛⬛🟧🟧🟧🟧🟧⬛⬛⬜⬜⬜"
		@echo "          ⬜⬜⬛🟧🟧🟧🟧🟧🟧🟧🟧🟧⬛⬜⬜"
		@echo "          ⬜⬛🟧🟧🟧🟧⬛⬛⬛🟧🟧🟧🟧⬛⬜"
		@echo "          ⬜⬛🟧🟧⬛⬛🟫🟫🟫⬛⬛🟧🟧⬛⬜"
		@echo "          ⬛🟧🟧⬛🟫⬜⬜🏼⬜⬜🟫⬛🟧🟧⬛"
		@echo "          ⬛🟧⬛🟫⬜⬜⬜⬜⬜⬜⬜🟫⬛🟧⬛"
		@echo "          ⬛🟧⬛🟫⬜⬜⬛⬜⬛⬜⬜🟫⬛🟧⬛"
		@echo "          ⬛🟧⬛🟫⬜⬜⬜⬜⬜⬜⬜🟫⬛🟧⬛"
		@echo "          ⬛🟧⬛🟫🟫⬜⬜🏼⬜⬜🟫🟫⬛🟧⬛"
		@echo "          ⬜⬛🟧⬛🟫🟫🏼🏼🏼🟫🟫⬛🟧⬛⬜"
		@echo "          ⬜⬛🟧🟧⬛⬛⬛⬛⬛⬛⬛🟧🟧⬛⬜"
		@echo "          ⬜⬜⬛🟧🟧🟧🟧⬛🟧🟧🟧🟧⬛⬜⬜"
		@echo "          ⬜⬜⬛⬛⬛🟧⬛🟧⬛🟧⬛⬛⬛⬜⬜"
		@echo "          ⬜⬛🟧🟧🟧⬛⬛⬛⬛⬛🟧🟧🟧⬛⬜"
		@echo "          ⬛🟧🟧⬛🟧🟧🟧⬛🟧🟧🟧⬛🟧🟧⬛"
		@echo "          ⬛⬛⬛⬛🟧🟧🟧⬛🟧🟧🟧⬛⬛⬛⬛"
		@echo "          ⬛🟫🟫⬛🟧🟧🟧⬛🟧🟧🟧⬛🟫🟫⬛"
		@echo "          ⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜"
		@echo "          ⬜⬜⬜⬛🟧🟧🟧⬛🟧🟧🟧⬛⬜⬜⬜"
		@echo "          ⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜"
