# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 16:19:11 by tsomchan          #+#    #+#              #
#    Updated: 2024/04/24 00:39:52 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT	=	client
SERVER	=	server

INC_PTH	=	inc/
INC		=	$(addprefix $(INC_PTH), minitalk.h)
	
SRC_PTH	=	src/
SRC		=	color.c util.c

SRC_S	=	$(SRC_PTH)server.c
SRC_C	=	$(SRC_PTH)client.c

BONUS_PTH	=	bonus/
BONUS_S	=	$(BONUS_PTH)server_bonus.c
BONUS_C	=	$(BONUS_PTH)client_bonus.c

CLIENT_B	=	client_bonus
SERVER_B	=	server_bonus

OBJ_PTH	=	obj/
OBJ		=	$(SRC:%.c=$(OBJ_PTH)%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
RM_RF	= 	rm -rf

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRC_S) $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@
	@echo "$(D_GREEN)$(SERVER) compiled$(NC)"

$(CLIENT): $(SRC_C) $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@
	@echo "$(D_GREEN)$(CLIENT) compiled$(NC)"

$(OBJ_PTH)%.o: $(SRC_PTH)%.c Makefile | $(OBJ_PTH)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
	@echo "$(D_YELLOW)compiled $<$(NC)"

$(OBJ_PTH):
	mkdir -p $(OBJ_PTH)
	@echo "$(D_YELLOW)compiled $@$(NC)"

clean:
	$(RM) $(OBJ)
	$(RM_RF) $(OBJ_PTH)
	@echo "$(D_GRAY)removed object files and dependency files$(NC)"

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(RM) $(SERVER_B) $(CLIENT_B)
	@echo "$(D_GRAY)removed $(SERVER) and $(CLIENT)$(NC)"

re: fclean all

#	bonus

bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER_B): $(BONUS_S) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(D_GREEN)$@ compiled$(NC)"

$(CLIENT_B): $(BONUS_C) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(D_GREEN)$@ compiled$(NC)"

#	my additional rules

#	Colors
NC			=	\033[0;0m
BLACK		=	\033[0;30m
D_RED		=	\033[0;31m
D_GREEN		=	\033[0;32m
D_YELLOW	=	\033[0;33m
D_BLUE		=	\033[0;34m
D_PURPLE	=	\033[0;35m
D_CYAN		=	\033[0;36m
L_GRAY		=	\033[0;37m
D_GRAY		=	\033[1;30m
L_RED		=	\033[1;31m
L_GREEN		=	\033[1;32m
L_YELLOW	=	\033[1;33m
L_BLUE		=	\033[1;34m
L_PURPLE	=	\033[1;35m
L_CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

clear:
	@clear

norm: clear
	@norminette $(addprefix $(SRC_PTH), $(SRC)) $(SRC_S) $(SRC_C)
TRASH = .DS_Store

clean_more:
	$(RM_RF) $(TRASH)

#	git

git: git_add push

log: clear
	@git log --name-status -3

push:
	@git push
	-@git push intra
	-@clear && git log --name-status -1

git_add:
	@git add .
ifdef m
	@git commit -m "$(m)"
endif

.PHONY += clear norm clean_more git log push git_add

#	test

t: all
	./client $(p) "asdf"

TXT_PTH	=	txt/

#	./client $(p) "$(cat file)"

define run_txt
	@echo "$(D_YELLOW)Makefile: ./client $(p)$$cat $(addprefix $(TXT_PTH), $1) $(NC)"
	./client $(p) "$(shell cat $(addprefix $(TXT_PTH), $1))"
endef

define bonus_txt
	@echo "$(D_YELLOW)Makefile: ./client_bonus $(p)$$cat $(addprefix $(TXT_PTH), $1) $(NC)"
	./client_bonus $(p) "$(shell cat $(addprefix $(TXT_PTH), $1))"
endef

test: all
ifdef txt
	@$(call run_txt, $(txt))
else
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
endif

#250k: all
#ifdef b
#	@$(call bonus_txt, 250k.txt)
#else
#	@$(call run_txt, 250k.txt)
#endif

100: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

50k: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

25k: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

eng: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

jp: all
ifdef b
	@$(call bonus_txt, jp_hira.txt)
	@$(call bonus_txt, jp_kata.txt)
else
	@$(call run_txt, jp_hira.txt)
	@$(call run_txt, jp_kata.txt)
endif

rus: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

ukr: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

gr: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

thai: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

emoji: all
ifdef b
	@$(call bonus_txt, $@.txt)
else
	@$(call run_txt, $@.txt)
endif

multi_thai: all
	@echo "$(D_YELLOW)1 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)2 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)3 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)4 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)5 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)6 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)7 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)8 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)9 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)10 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)11 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)12 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)13 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)14 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)15 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)16 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)17 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)18 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)19 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif
	@echo "$(D_YELLOW)20 $(NC)"
ifdef b
	@$(call bonus_txt, thai.txt)
else
	@$(call run_txt, thai.txt)
endif

multi_50k: all
	@echo "$(D_YELLOW)1 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)2 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)3 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)4 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)5 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)6 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)7 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)8 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)9 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)10 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)11 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)12 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)13 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)14 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)15 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)16 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)17 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)18 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)19 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif
	@echo "$(D_YELLOW)20 $(NC)"
ifdef b
	@$(call bonus_txt, 50k.txt)
else
	@$(call run_txt, 50k.txt)
endif

test_all: 100 jp rus ukr gr emoji 25k 50k thai 