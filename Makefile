# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 21:43:02 by cmoura-p          #+#    #+#              #
#    Updated: 2024/12/17 19:21:49 by cmoura-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC =		cc -g
CFLAGS =	-Wall -Wextra -Werror
READLINE_FLAG = -lreadline

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =		main.c \
			src/init/handle_signals.c \
			src/init/init.c \
			src/init/check_syntax.c \
			src/init/utils_syntax.c \
			src/clear/free_funcs.c \
			src/parser/parsing.c

OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

VALGRIND_FLAGS = --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $@ $(OBJS) $(LIBFT) $(READLINE_FLAG)

# Regra para compilar arquivos fonte em arquivos objeto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)/src/init $(OBJ_DIR)/src/clear $(OBJ_DIR)/src/parser
	@$(CC) $(CFLAGS) -c $< -o $@

# Regras para criar subdiretórios necessários no OBJ_DIR
$(OBJ_DIR)/src/init:
	@mkdir -p $@

$(OBJ_DIR)/src/clear:
	@mkdir -p $@

$(OBJ_DIR)/src/parser:
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT):
	@make -C $(LIBFT_DIR) -s

valgrind: all
	valgrind $(VALGRIND_FLAGS) $(VALGRIND_SUPP) ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) -s

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) -s

re: fclean all

