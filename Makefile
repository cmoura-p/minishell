# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 16:11:54 by joseoliv          #+#    #+#              #
#    Updated: 2024/12/12 14:55:44 by cmoura-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC =		cc -g
CFLAGS =	-Wall -Wextra -Werror
READLINE_FLAG = -lreadline

SRC =		main.c \
			src/init/handle_signals.c \
			src/init/init.c \
			src/init/check_syntax.c \
			src/init/utils_syntax.c \
			src/clear/free_funcs.c \
			src/parser/parsing.c

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $@ $(OBJ) $(LIBFT) $(READLINE_FLAG)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) -s

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR) -s

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) -s

re: fclean all
