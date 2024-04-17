# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 20:20:26 by memahote          #+#    #+#              #
#    Updated: 2023/10/27 20:20:26 by memahote         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC_DIR 	= includes/
SRC_DIR 	= srcs/
OBJ_DIR		= 	obj/

SRC =  get_time.c host.c init.c parse.c philo.c routine.c utils.c

SRC_PATH 	= $(addprefix $(SRC_DIR), $(SRC))
OBJ      	= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_PATH))
INC			= $(addprefix $(INC_DIR), philo.h)
DEP			= $(patsubst %.c, $(OBJ_DIR)%.d, $(SRC_PATH))

CC				= cc
RM				= rm -rf
FLAGS			= -Wall -Wextra -Werror -pthread 
DEP_FLAGS		= -MMD -MP
MKDIR           = mkdir -p
MAKE            = make -C



.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJ) 
	@cc $(FLAGS) -o $(NAME) $(OBJ) 

-include $(DEP)

$(OBJ_DIR)%.o: %.c 
	$(MKDIR) $(@D)
	$(CC) $(FLAGS) $(DEP_FLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all