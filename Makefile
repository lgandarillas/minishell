# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgandari_aquinter <marvin@42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 00:00:00 by lgandari_aquinter #+#    #+#              #
#    Updated: 2024/07/02 18:30:02 by lgandari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME_LG	= minishell_lg
NAME_AQ	= minishell_aq

RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m 

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address
CC		= cc
RM		= rm -f

LIBFT	= libft_v2//libft_v2.a
LIBFT_PATH	= libft_v2/

SRC_DIR		= src/
SRC_LG		= src_lg/
SRC_AQ		= src_aq/

SRCS	= $(addprefix $(SRC_DIR), main.c)
SRCS_LG	= $(addprefix $(SRC_LG), main.c)
SRCS_AQ	= $(addprefix $(SRC_AQ), main.c)

OBJS	= $(SRCS:.c=.o)
OBJS_LG	= $(SRCS_LG:.c=.o)
OBJS_AQ	= $(SRCS_AQ:.c=.o)

all : $(NAME)
lg : $(NAME_LG)
aq : $(NAME_AQ)

$(NAME) : $(OBJS)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) -I ../../inc/minishell.h $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compiling minishell...$(NC)"

$(NAME_LG) : $(OBJS_LG)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS_LG) -I ../../inc/minishell.h $(LIBFT) -o $(NAME_LG)
	@echo "$(GREEN)Compiling minishell...$(NC)"

$(NAME_AQ) : $(OBJS_AQ)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS_AQ) -I ../../inc/minishell.h $(LIBFT) -o $(NAME_AQ)
	@echo "$(GREEN)Compiling minishell...$(NC)"

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_LG)
	@$(RM) $(OBJS_AQ)
	@make clean -sC $(LIBFT_PATH)
	@echo "$(RED)All Objs Deleted.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_LG)
	@$(RM) $(NAME_AQ)
	@$(RM) $(OBJS_LG)
	@$(RM) $(OBJS_AQ)
	@$(RM) $(LIBFT)
	@echo "$(RED)Everything Deleted.$(NC)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
