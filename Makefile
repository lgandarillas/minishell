# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 00:00:00 by lgandari_aq       #+#    #+#              #
#    Updated: 2024/07/10 20:59:56 by aquinter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME_LG	= minishell_lg
NAME_AQ	= minishell_aq

RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m 

CFLAGS	= -Wall -Werror -Wextra -g3 #-fsanitize=address
RLFLAG 	= -lreadline
CC		= cc
RM		= rm -f

LIBFT	= libft_v2//libft_v2.a
LIBFT_PATH	= libft_v2/

SRC_DIR		= src/
SRC_LG		= src_lg/
SRC_AQ		= src_aq/

SRCS	= $(addprefix $(SRC_DIR), main.c)
SRCS_LG	= $(addprefix $(SRC_LG), main.c init_shell.c error.c exit.c)
SRCS_AQ	= $(addprefix $(SRC_AQ), \
			main.c			init_shell.c	error.c		exit.c 		\
			ft_cd.c 		ft_getenv.c 	ft_setenv.c ft_pwd.c 	\
			ft_export.c		ft_env.c		ft_addenv.c)

OBJS	= $(SRCS:.c=.o)
OBJS_LG	= $(SRCS_LG:.c=.o)
OBJS_AQ	= $(SRCS_AQ:.c=.o)

all : $(NAME)
lg : $(NAME_LG)
aq : $(NAME_AQ)

$(NAME) : $(OBJS)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) -I ../../inc/minishell.h $(LIBFT) $(RLFLAG) -o $(NAME)
	@echo "$(GREEN)Compiling minishell...$(NC)"

$(NAME_LG) : $(OBJS_LG)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS_LG) -I ../../inc/minishell.h $(LIBFT) $(RLFLAG) -o $(NAME_LG)
	@echo "$(GREEN)Compiling minishell...$(NC)"

$(NAME_AQ) : $(OBJS_AQ)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS_AQ) -I ../../inc/minishell.h $(LIBFT) $(RLFLAG) -o $(NAME_AQ)
	@echo "$(GREEN)Compiling minishell...$(NC)"
	@echo "$(GREEN)Enjoy!$(NC)"

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

reaq: fclean aq

.PHONY: all clean fclean re reaq
.SILENT:
