# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/31 01:17:29 by ivromero          #+#    #+#              #
#    Updated: 2024/05/18 16:04:36 by ivromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
#BONUS_NAME 	= minishell_bonus

SRC_PATH		= ./src/
SRCBONUS_PATH	= ./src_bonus/

CC				= gcc
RM				= rm -f
AR				= ar rcs

#LIBFT_LIB 		= libft/
#LIBFT_FLAGS 	= -L libft/ -lft
RL_FLAGS 		= -lreadline
CFLAGS 			= -Wall -Wextra -Werror -Wpedantic #-g -fsanitize=address #-fsanitize=thread # 
DEBUG_FLAGS 	= -Wall -Wextra -Werror -g3 -D DEBUG=2 #-fsanitize=address
VALGRIND_FLAGS 	= -Wall -Wextra -Werror #-g 
HELGRIND_FLAGS 	= -Wall -Wextra -Werror #-g #-fsanitize=thread bloquea ordenador
VALGR_RUN_FLAGS	= --leak-check=full --show-leak-kinds=all --track-origins=yes

REPO_PATH		= ./repo/
#EX_PATH			= ./ex01/
#BONUS_PATH		= ./

REPGIT_URL		= git@github.com:imero-dev/minishell.git

#ARGS			= 200 60 60 60

#default: test testv testh# all

##########################################################################################
##########################################################################################

NAME_DEBUG 		= $(NAME)_debug
NAME_VALGR 		= $(NAME)_valgr

OBJ_PATH		= ./obj/
OBJDBG_PATH		= ./obj_debug/
OBJVLG_PATH		= ./obj_valgr/

SRC_NAME 		= $(shell find $(SRC_PATH) -type f -name "*.c" -exec basename {} \;)
SRCBONUS_NAME 	= $(shell find $(SRCBONUS_PATH) -type f -name "*.c" -exec basename {} \;)
H_FILES			= $(wildcard $(SRC_PATH)*.h)

OBJ_NAME		= $(SRC_NAME:.c=.o)
OBJBONUS_NAME	= $(SRCBONUS_NAME:.c=.o)
HBONUS_FILES	= $(wildcard $(SRCBONUS_PATH)*.h)

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

all:	 .init $(NAME) .anime

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH)
#		@echo "\e[u🟧\e[s"
		@$(CC) $(CFLAGS) -o $@ -c $<
		@echo -n 🟧

$(OBJDBG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJDBG_PATH)
		@$(CC) $(DEBUG_FLAGS) -o $@ -c $<
		@echo -n 🟧

$(OBJVLG_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJVLG_PATH)
		@$(CC) $(VALGRIND_FLAGS) -o $@ -c $<
		@echo -n 🟧

$(NAME): $(OBJS) $(H_FILES)
		@echo 
#		@make -C $(LIBFT_LIB) 
#		@if [ ! -f "readline-8.2/readline.h" ]; then wget ftp://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz; tar -xvzf readline-8.2.tar.gz; fi;
		@echo "$(ORANGE)Linking:$(NC) $@"
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  $(RL_FLAGS)
		@touch .init
		@echo "$(GREEN)Finished:$(NC) $@"

.init:
		@echo ""
		@echo "$(BLUE)$(NAME) compiling from scratch:$(NC)"
		@echo -n "\e[s⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️⬛️\e[u"

#bonus: $(BONUS_NAME)

#$(BONUS_NAME): $(OBJSBONUS)
##		@make -C $(LIBFT_LIB) > /dev/null
#		@$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(OBJSBONUS)-o $(BONUS_NAME)
#		@echo "$(GREEN)Compilación terminada:$(NC) $@"
#		@#make info


clean:
		@$(RM) $(OBJS) $(OBJSBONUS) $(OBJS_DEBUG) $(OBJS_VALGR) .init
		@$(RM) -rf $(OBJ_PATH) $(OBJDBG_PATH) $(OBJVLG_PATH)
#		@make -C $(LIBFT_LIB) clean 
		@echo "$(GREEN)clean done:$(NC) $(NAME)"

fclean:	clean
		@$(RM) $(NAME) $(BONUS_NAME) $(NAME_DEBUG) $(BONUS_NAME)_debug $(NAME_VALGR) .init
		@$(RM) -rf *.dSYM
#		@make -C $(LIBFT_LIB) fclean
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

debug-re:fclean debug

debug:	$(NAME_DEBUG)

$(NAME_DEBUG): $(OBJS_DEBUG)
		@echo "flags: $(DEBUG_FLAGS)"
#		@make -C $(LIBFT_LIB) debug DEBUG_FLAGS="$(DEBUG_FLAGS)"
		$(CC) $(DEBUG_FLAGS) $(OBJS_DEBUG) -o $(NAME_DEBUG)
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
#		@make -C $(LIBFT_LIB) valgrind
		$(CC) $(VALGRIND_FLAGS) $(OBJS_VALGR) -o $(NAME_VALGR)
		@echo "Compilación terminada: $@"
		
clean_valgr:
		@$(RM) $(OBJS_VALGR) $(NAME_VALGR)
		@$(RM) -rf $(OBJVLG_PATH) *.dSYM
		@echo "$(GREEN)clean done:$(NC) $(NAME_VALGR)"

test: all
		@echo "$(GREEN)Testing: $(ARGS)$(NC)"
		./$(NAME) $(ARGS)
		@echo "$(GREEN)make test ARGS=\"$(ARGS)$(NC)\""

testd: $(NAME_DEBUG)
		@echo "$(GREEN)Testing: $(ARGS)$(NC)"
		./$(NAME_DEBUG) $(ARGS)

testv: valgrind
#		--tool=memcheck
		$(call valgrind_test,$(ARGS),"Con los args de test: $(ARGS)")
#		ulimit -v 160000; valgrind --leak-check=full --errors-for-leak-kinds=all  ./$(NAME_VALGR) 85 60 60 60
	
testh: helgrind
		$(call helgrind_test,$(ARGS),"Con los args de test: $(ARGS)")


tests: all
		@echo "$(GREEN)Evaluation$(NC)"
		norminette; true;

		$(call test_run,1 800 200 200,"El filósofo no debería comer y debería morir entre 800 y 810.")
		$(call test_run,5 800 200 200,"Ningún filósofo debería morir", & sleep 60s; pkill $(NAME)) 
		$(call test_run,5 800 200 200 7,"Ningún filósofo debería morir y la simulación debería detenerse cuando todos los filósofos hayan comido al menos 7 veces.")
		$(call test_run,4 410 200 200,"Ningún filósofo debería morir", & sleep 60s; pkill $(NAME))
		$(call test_run,4 310 200 100,"Un filósofo debería morir entre 310 y 320.")
		@echo "Para mas test prueba: $(GREEN)make tester$(NC)" 

tester: all
		@if [ ! -f "minishell_tester/tester" ]; then git clone https://github.com/LucasKuhn/minishell_tester.git; fi;
		cd minishell_tester && bash tester;
#		@if [ ! -f "thales_tester/test.sh" ]; then git clone https://github.com/Rz-Rz/thales_tester.git; fi;
#		chmod +x thales_tester/test.sh 
#		cd thales_tester && ./test.sh ../ 1
#		python3 *.py

commit:
ifndef MSG
		@echo "Please provide a commit message using: make commit MSG=\"your message\""
else
		@echo "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜   GIT HUB    ⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️"
		@norminette || make pregunta
		@make fclean
		git add ../.
		@make info2 > .info
		git status
		@make pregunta
		git commit -a -m "$(NAME): $(MSG)"
		git push
		@echo "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜   VOGSPHERE  ⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️"
#		@$(RM) -rf $(REPO_PATH)/*
#		@cp -r $(LIBFT_LIB) $(REPO_PATH)$(LIBFT_LIB)
		@echo "Vamos a borrar la carpeta $(REPO_PATH)"
		@make pregunta
		@$(RM) -rf $(REPO_PATH)
		@git clone $(REPGIT_URL) $(REPO_PATH)
		@mkdir -p "$(REPO_PATH)$(EX_PATH)"
		@mkdir -p "$(REPO_PATH)$(EX_PATH)$(SRC_PATH)"
		@cp  $(SRC) $(REPO_PATH)$(EX_PATH)$(SRC_PATH)
		@cp  $(H_FILES) $(REPO_PATH)$(EX_PATH)$(H_FILES)
		@cp Makefile $(REPO_PATH)$(EX_PATH)Makefile
		@cd $(REPO_PATH) && git add . && git status
		@make pregunta
		@cd $(REPO_PATH) && git commit -a -m "$(MSG)" && git push && git log
		@echo "Vamos a clonar la repo en la carpeta test"
		@make pregunta
		@$(RM) -rf test
		@git clone $(REPO_PATH) test
#		@cp checker_Mac test/
endif

define run_block
	@echo ""
	@echo "🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩"
	@echo "$(BLUE)$(3)> $(GREEN)./$(NAME) $(1)$(NC)"
	$(call question,$(2))
	$(4); true
	@echo "🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧"
endef

define test_run
	$(call run_block,$(1),$(2),testing,./$(NAME) $(1)$(3))
endef

define valgrind_test
	$(call run_block,$(1),$(2),valgrind, valgrind $(VALGR_RUN_FLAGS) ./$(NAME_VALGR) $(1))
endef

define helgrind_test
	$(call run_block,$(1),$(2),helgrind, valgrind --tool=helgrind ./$(NAME_VALGR) $(1))
endef

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
		@make info2
		@make info2 > .info

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
		@make pregunta > /dev/null
		@touch .anime
		@clear
		@make cabecera keny
		@make cabecera ps0 
		@make cabecera ps1 
		@make cabecera ps0 
		@make cabecera ps1 
		@make cabecera ps0 
		@make cabecera ps1 

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