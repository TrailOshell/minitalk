# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 16:19:11 by tsomchan          #+#    #+#              #
#    Updated: 2024/04/15 16:19:14 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT	=	client
SERVER	=	server

INC_PTH	=	inc/
INC		=	$(addprefix $(INC_PTH), minitalk.h)

SRC_PTH	=	src/
SRC_S	=	server.c
SRC_C	=	client.c

OBJ_PTH	=	obj/
OBJ		=	$(SRC:%.c=$(OBJ_PTH)%.o)
OBJ_S	=	$(SRC_S:%.c=$(OBJ_PTH)%.o)
OBJ_C	=	$(SRC_C:%.c=$(OBJ_PTH)%.o)

CC		=	cc 
CFLAGS	=	-Wall -Wextra -Werror 
RM		=	rm -f
RM_RF	= 	rm -rf

all : $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(D_GREEN)$(SERVER) compiled$(NC)"

$(CLIENT): $(OBJ_C) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(D_GREEN)$(CLIENT) compiled$(NC)"

$(OBJ_PTH)%.o: $(SRC_PTH)%.c $(INC) Makefile | $(OBJ_PTH)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
	@echo "$(D_YELLOW)compiled $<$(NC)"

$(OBJ_PTH):
	mkdir -p $(OBJ_PTH)
	@echo "$(D_YELLOW)compiled $@$(NC)"

clean:
	$(RM) $(OBJ)
	$(RM_RF) $(OBJ_PTH)
	@echo "$(D_GRAY)removed object files$(NC)"

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@echo "$(D_GRAY)removed $(SERVER)$(NC)"
	@echo "$(D_GRAY)removed $(CLIENT)$(NC)"

re: fclean all

.PHONY: clean fclean re all server client

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
	@norminette $(addprefix $(SRC_PTH), $(SRC))

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