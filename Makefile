# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/31 01:17:29 by ivromero          #+#    #+#              #
#    Updated: 2024/09/29 01:11:32 by ivromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
#BONUS_NAME 	= minishell_bonus

SRC_PATH		= ./src/
SRCBONUS_PATH	= ./src_bonus/

CC				= gcc
RM				= rm -f
AR				= ar rcs

LIBFT_PATH 		= libft/
LIBS_FLAGS 		= -lreadline -L $(LIBFT_PATH) -lft
CFLAGS 			= -Wall -Wextra -Werror -Wpedantic -pedantic -g #-fsanitize=address #-fsanitize=thread # 
DEBUG_FLAGS 	= -Wall -Wextra -Werror -g -D DEBUG=2 #-fsanitize=address
VALGRIND_FLAGS 	= -Wall -Wextra -Werror -g 
HELGRIND_FLAGS 	= -Wall -Wextra -Werror -g #-fsanitize=thread bloquea ordenador
VALGR_RUN_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=yes  --suppressions=./readline.supp

REPO_PATH		= ./repo/
#EX_PATH		= ./ex01/
#BONUS_PATH		= ./

REPGIT_URL		= git@github.com:imero-dev/minishell.git

#ARGS			= 200 60 60 60

default: all .anime #test testv testh# all

##########################################################################################
##########################################################################################

NAME_DEBUG 		= $(NAME)_debug
NAME_VALGR 		= $(NAME)_valgr

OBJ_PATH		= ./obj/
OBJDBG_PATH		= ./obj_debug/
OBJVLG_PATH		= ./obj_valgr/

SRC_NAME 		= btin_dirs.c               com_ouput_redirections.c  syntax_classify_tokens.c \
btin_echo.c               com_run.c                 syntax_expand_env.c \
btin_exit.c               com_run_utils.c           syntax_interpreter.c \
btin_export.c             env_funcs.c               syntax_interpreter_funcs.c \
btin_unset.c              env_utils.c               syntax_spliter.c \
com_find.c                minishell.c               syntax_spliter_utils.c \
com_funcs.c               com_input_redirections.c  signals.c
SRCBONUS_NAME 	= 
H_FILES			= src/minishell.h

OBJ_NAME		= $(SRC_NAME:.c=.o)
OBJBONUS_NAME	= $(SRCBONUS_NAME:.c=.o)
HBONUS_FILES	= 

ifeq (BONUS, 1)
SRC_NAME		+= $(SRCBONUS_NAME)
OBJ_NAME		+= $(OBJBONUS_NAME)
H_FILES			+= $(HBONUS_FILES)
endif


SRC				= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJS_DEBUG		= $(addprefix $(OBJDBG_PATH), $(OBJ_NAME))
OBJS_VALGR		= $(addprefix $(OBJVLG_PATH), $(OBJ_NAME))
#OBJSBONUS 		= $(SRCBONUS:.c=.o)

ifeq ($(UNAME), Darwin)
CFLAGS		+= -D MACOS=1
else ifeq ($(UNAME), Linux)
CFLAGS		+= -D LINUX=1
endif

RED			= \e[0;31m
ORANGE		= \e[0;33m
GREEN		= \e[0;32m
BLUE		= \e[1;34m\e[4m
NC			= \e[0m

COMPILED	= 0

##########################################################################################
##########################################################################################

all:	 
		@$(MAKE) -C $(LIBFT_PATH) all
		@$(MAKE) .init $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH)
		@echo "\e[u🟧\e[s"
#		@$(foreach i,$(shell seq 1 $(COMPILED)), \
		echo "";)
		$(CC) $(CFLAGS) -o $@ -c $<
		$(eval COMPILED = $(shell echo $$(($(COMPILED) + 1)) ))
#		@echo -n 🟧

$(NAME): $(OBJS) $(H_FILES) $(LIBFT_PATH)libft.a
#		@if [ ! -f "readline-8.2/readline.h" ]; then wget ftp://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz; tar -xvzf readline-8.2.tar.gz; fi;
		@echo "$(GREEN)$(COMPILED) .obj compiled$(NC)"
		@echo "$(ORANGE)Linking:$(NC) $@"
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS_FLAGS)
		@echo "$(GREEN)Finished:$(NC) $@"
#		@$(MAKE)  .anime

.init: 
#		@echo ""
		@echo "$(BLUE)Building $(NAME):$(NC)"
		@echo -n "⬛\e[s"
		@for i in $(OBJS); do \
			echo -n "⬛"; \
		done
		@echo "⬛"
		
#		@for i in $(OBJS); do \
#			echo ""; \
#		done

#bonus: $(BONUS_NAME)

#$(BONUS_NAME): $(OBJSBONUS)
##		@$(MAKE) -C $(LIBFT_PATH) > /dev/null
#		@$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(OBJSBONUS)-o $(BONUS_NAME)
#		@echo "$(GREEN)Compilación terminada:$(NC) $@"
#		@#make info


clean:
		@$(RM) $(OBJS) $(OBJSBONUS) $(OBJS_DEBUG) $(OBJS_VALGR)
		@$(RM) -rf $(OBJ_PATH) $(OBJDBG_PATH) $(OBJVLG_PATH)
		@$(MAKE) -C $(LIBFT_PATH) clean 
		@echo "$(GREEN)clean done:$(NC) $(NAME)"

fclean:	clean
		@$(RM) $(NAME) $(BONUS_NAME) $(NAME_DEBUG) $(BONUS_NAME)_debug $(NAME_VALGR)
		@$(RM) -rf *.dSYM
		@$(MAKE) -C $(LIBFT_PATH) fclean
		@echo "$(GREEN)fclean done:$(NC) $(NAME)"

re:		fclean all

.PHONY : all clean fclean re info normi test tester commit anime debug valgrind norminette debug-re #bonus

##########################################################################################
############################ EXTRA RULES ################################################
##########################################################################################

prueba:
		ARGS="4 5 5 1"
		@echo "$(ARGS)"

normi:
		@norminette $(SRC) $(H_FILES) | awk '/Error|Warning/ {if(/src/) printf "$(RED)%s$(NC)\n", $$0; else print $$0}'

norminette:
		@norminette | awk '/Error|Warning/ {if(/src/) printf "$(RED)%s$(NC)\n", $$0; else print $$0}'
#		| grep -E "(Error|Warning)" | grep --color=always -E 'src\|' ; true
#       | (grep --color=always -E '.c' || cat)
#		@norminette src/*.c src_bonus/*.c libft/*.c libft/*.h headers/*.h | grep -E '(Error|Warning)' ; true

$(OBJDBG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJDBG_PATH)
		@$(CC) $(DEBUG_FLAGS) -o $@ -c $<
		@echo -n 🟧

$(OBJVLG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJVLG_PATH)
		@$(CC) $(VALGRIND_FLAGS) -o $@ -c $<
		@echo -n 🟧

debug-re:fclean debug

debug:	$(NAME_DEBUG)

$(NAME_DEBUG): $(OBJS_DEBUG)
		@echo "flags: $(DEBUG_FLAGS)"
		@$(MAKE) -C $(LIBFT_PATH) debug DEBUG_FLAGS="$(DEBUG_FLAGS)"
		$(CC) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $(NAME_DEBUG) $(LIBS_FLAGS)_debug
		@echo "Compilación terminada: $@"
		
lldb: $(NAME_DEBUG)
		lldb -- ./$(NAME_DEBUG) $(ARGS)

gdb: $(NAME_DEBUG)
		gdb --args ./$(NAME_DEBUG) $(ARGS)

valgrind: $(NAME_VALGR)

helgrind:
		make valgrind VALGRIND_FLAGS="$(HELGRIND_FLAGS)"

$(NAME_VALGR): clean_valgr $(OBJS_VALGR)
		@echo "flags: $(VALGRIND_FLAGS)"
		@$(MAKE) -C $(LIBFT_PATH) valgrind
		$(CC) $(VALGRIND_FLAGS) $(OBJS_VALGR) -o $(NAME_VALGR) $(LIBS_FLAGS)_valgr
		@echo "Compilación terminada: $@"
		
clean_valgr:
		@$(RM) $(OBJS_VALGR) $(NAME_VALGR)
		@$(RM) -rf $(OBJVLG_PATH) *.dSYM
		@echo "$(GREEN)clean done:$(NC) $(NAME_VALGR)"

test: all
		@echo "$(GREEN)Testing: $(ARGS)$(NC)"
		./$(NAME) $(ARGS)

testd: $(NAME_DEBUG)
		@echo "$(GREEN)Testing debug: $(ARGS)$(NC)"
		./$(NAME_DEBUG) $(ARGS)

testv: valgrind
		@echo "$(GREEN)Testing Valgrind: $(ARGS)$(NC)"
#		--tool=memcheck
		valgrind $(VALGR_RUN_FLAGS) ./$(NAME_VALGR)
#		ulimit -v 160000; valgrind --leak-check=full --errors-for-leak-kinds=all  ./$(NAME_VALGR) 85 60 60 60
	
testh: helgrind
		$(call helgrind_test,$(ARGS),"Con los args de test: $(ARGS)")


tests: all
		@echo "$(GREEN)Evaluation$(NC)"
		norminette; true;

		@echo "Para mas test prueba: $(GREEN)make tester$(NC)" 

tester: all
		@if [ ! -f "minishell_tester/tester" ]; then git clone https://github.com/LucasKuhn/minishell_tester.git; fi;
		cp tests minishell_tester/tests
		cd minishell_tester && bash tester tests; true;
		make pregunta
		cd minishell_tester && bash tester builtins; true;
		make pregunta
		cd minishell_tester && bash tester extras; true;
		make pregunta
		cd minishell_tester && bash tester redirects; true;
		make pregunta
		cd minishell_tester && bash tester pipes; true;
		make pregunta
		cd minishell_tester && bash tester

mpanic: all
		@if [ ! -f "mpanic/mpanic.sh" ]; then git clone git@github.com:ChewyToast/mpanic.git; fi;
		cd mpanic && bash mpanic.sh; true;

commit:
ifndef MSG
		@echo "Please provide a commit message using: make commit MSG=\"your message\""
else
		@echo "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜   GIT HUB    ⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️"
		@norminette || make pregunta
		@$(MAKE) fclean
		git add ../.
		@$(MAKE) info2 > .info
		git status
		@$(MAKE) pregunta
		git commit -a -m "$(NAME): $(MSG)"
		git push
		@echo "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜   VOGSPHERE  ⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️"
#		@$(RM) -rf $(REPO_PATH)/*
#		@cp -r $(LIBFT_PATH) $(REPO_PATH)$(LIBFT_PATH)
		@echo "Vamos a borrar la carpeta $(REPO_PATH)"
		@$(MAKE) pregunta
		@$(RM) -rf $(REPO_PATH)
		@git clone $(REPGIT_URL) $(REPO_PATH)
		@mkdir -p "$(REPO_PATH)$(EX_PATH)"
		@mkdir -p "$(REPO_PATH)$(EX_PATH)$(SRC_PATH)"
		@cp -r $(LIBFT_PATH) $(REPO_PATH)
		@cp  $(SRC) $(REPO_PATH)$(EX_PATH)$(SRC_PATH)
		@cp  $(H_FILES) $(REPO_PATH)$(EX_PATH)$(H_FILES)
		@cp Makefile $(REPO_PATH)$(EX_PATH)Makefile
		@cd $(REPO_PATH) && git add . && git status
		@$(MAKE) pregunta
		@cd $(REPO_PATH) && git commit -a -m "$(MSG)" && git push && git log
		@echo "Vamos a clonar la repo en la carpeta test"
		@$(MAKE) pregunta
		@$(RM) -rf test
		@git clone $(REPO_PATH) test
#		@cp checker_Mac test/
endif

define question
	@echo "$(ORANGE)$(1)$(NC)"
	@echo "$(GREEN)Do you want to continue? (Y/n) $(NC)"
	@read answer; \
	if [ "$$answer" != "y" ] && [ "$$answer" != "Y" ] && [ "$$answer" != "" ]; then \
		echo "God bye!!!"; \
		exit 1; \
	fi
endef

pregunta:
		@echo "$(GREEN)¿Deseas continuar? (S/n) $(NC)"; \
		read respuesta; \
		if [ "$$respuesta" != "s" ] && [ "$$respuesta" != "S" ] && [ "$$respuesta" != "" ]; then \
			echo "God bye!!!"; \
			exit 1; \
		fi


info:
		@$(MAKE) info2
		@$(MAKE) info2 > .info

info2:
		@echo "Ficheros:"
		@echo $(SRC) | wc -w

		@echo "Funciones:"
		@cat $(SRC) | grep -x "{" | wc -l
		@echo "Lineas:"
		@cat $(SRC) | wc -l
#		@echo "Funciones bonus:"
#		@cat $(SRCBONUS) | grep -x "{" | wc -l

##########################################################################################
##########################################################################################

.anime:

		@echo "Presiona intro para continuar"
		@$(MAKE) pregunta > /dev/null
		@touch .anime
		@clear
		@$(MAKE) cabecera keny
		@$(MAKE) cabecera ps0 
		@$(MAKE) cabecera ps1 
		@$(MAKE) cabecera ps0 
		@$(MAKE) cabecera ps1 
		@$(MAKE) cabecera ps0 
		@$(MAKE) cabecera ps1 

keny:
		@echo "            ⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜"
		@echo "            ⬜⬜⬜⬛⬛🟧🟧🟧🟧🟧⬛⬛⬜⬜⬜"
		@echo "            ⬜⬜⬛🟧🟧🟧🟧🟧🟧🟧🟧🟧⬛⬜⬜"
		@echo "            ⬜⬛🟧🟧🟧🟧⬛⬛⬛🟧🟧🟧🟧⬛⬜"
		@echo "            ⬜⬛🟧🟧⬛⬛🟫🟫🟫⬛⬛🟧🟧⬛⬜"
		@echo "            ⬛🟧🟧⬛🟫⬜⬜🏼⬜⬜🟫⬛🟧🟧⬛"
		@echo "            ⬛🟧⬛🟫⬜⬜⬜⬜⬜⬜⬜🟫⬛🟧⬛"
		@echo "            ⬛🟧⬛🟫⬜⬜⬛⬜⬛⬜⬜🟫⬛🟧⬛"
		@echo "            ⬛🟧⬛🟫⬜⬜⬜⬜⬜⬜⬜🟫⬛🟧⬛"
		@echo "            ⬛🟧⬛🟫🟫⬜⬜🏼⬜⬜🟫🟫⬛🟧⬛"
		@echo "            ⬜⬛🟧⬛🟫🟫🏼🏼🏼🟫🟫⬛🟧⬛⬜"
		@echo "            ⬜⬛🟧🟧⬛⬛⬛⬛⬛⬛⬛🟧🟧⬛⬜"
		@echo "            ⬜⬜⬛🟧🟧🟧🟧⬛🟧🟧🟧🟧⬛⬜⬜"
		@echo "            ⬜⬜⬛⬛⬛🟧⬛🟧⬛🟧⬛⬛⬛⬜⬜"
		@echo ""
		@echo "      _                                                _ _                    "
		@echo "     (_)_   ___ __ ___  _ __ ___   ___ _ __ ___       (_) |__   __ _ _______  "
		@echo "     | \ \ / /  __/ _ \| '_ ' _ \ / _ \  __/ _ \      | | '_ \ / _\` |_  / _ \ "
		@echo "     | |\ V /| | ( (_) | | | | | |  __/ | ( (_) )     | | |_) | (_| |/ / (_) |"
		@echo "     |_| \_/ |_|  \___/|_| |_| |_|\___|_|  \___/      |_|_.__/ \__,_/___\___/ "
		@sleep 2  
		@clear







cabecera:
		@sleep 0.8
		@echo "\e[H"
		@echo "🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧"
		@echo "🟧                                                                                                🟧"
		@echo "🟧                                        🖥️  $(GREEN)minishell$(NC)  🖥️                                         🟧"
		@echo "🟧                                                                                                🟧"
		@echo "🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧"
		@echo  
		 



ps0:
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️> ⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"

ps1:
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️>⎕⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"
		@echo "                   ⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️"

#http://es.tldp.org/COMO-INSFLUG/COMOs/Bash-Prompt-Como/Bash-Prompt-Como-5.html
#https://www.cyberciti.biz/tips/howto-linux-unix-bash-shell-setup-prompt.html