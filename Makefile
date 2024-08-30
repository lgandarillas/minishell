# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 00:00:00 by lgandari_aq       #+#    #+#              #
#    Updated: 2024/08/30 11:33:27 by lgandari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m 

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address
RLFLAG 	= -lreadline
CC		= cc
RM		= rm -f

LIBFT	= libft_v2//libft_v2.a
LIBFT_PATH	= libft_v2/

SRC_DIR		= src/

SRCS	= $(addprefix $(SRC_DIR), \
	main.c				\
	init/init_shell.c		\
	init/error.c			\
	init/path.c			\
	lexer/check_prompt.c		\
	lexer/lexer_utils.c 		\
	lexer/lexer.c			\
	lexer/token_list.c		\
	lexer/check_brackets.c		\
	lexer/analyze_token_type.c	\
	parser/parser.c	\
	expander/expander.c		\
	expander/expand_variables.c	\
	expander/quote_management.c	\
	expander/word_splitter.c	\
	expander/quote_cleaner.c	\
	expander/expand_status.c	\
	env/ft_addenv.c 		\
	env/ft_getenv.c 		\
	env/ft_setenv.c 		\
	env/ft_delenv.c 		\
	builtins/ft_pwd.c 		\
	builtins/ft_export.c 		\
	builtins/ft_env.c 		\
	builtins/ft_cd.c 		\
	builtins/ft_unset.c 		\
	builtins/ft_echo.c		\
	builtins/ft_exit.c		\
	builtins/utils.c		\
	builtins/init_builtins.c		\
	executor/executor.c		\
	signals/init_signals.c	\
	signals/eof.c			\
	signals/quit.c			\
	signals/interrupt.c		\
	heredoc/heredoc.c		\
	)

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) -I ../../inc/minishell.h $(LIBFT) $(RLFLAG) -o $(NAME)
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

reaq: fclean aq

.PHONY: all clean fclean re reaq
.SILENT:
