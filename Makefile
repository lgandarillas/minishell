# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgandari_aquinter <marvin@42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 00:00:00 by lgandari_aquinter #+#    #+#              #
#    Updated: 2024/07/02 16:31:01 by lgandari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m 

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address
CC		= cc
RM		= rm -f

LIBFT	= libft_v2//libft_v2.a
LIBFT_PATH	= libft_v2/

SRC_DIR	= src/
SRCS	= $(addprefix $(SRC_DIR), main.c)
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) -I ../../inc/minishell.h $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compiling minishell...$(NC)"

clean:
	@$(RM) $(OBJS)
	@make clean -sC $(LIBFT_PATH)
	@echo "$(RED)All Objs Deleted.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(RED)Everything Deleted.$(NC)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
