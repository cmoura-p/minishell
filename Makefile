# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 21:43:02 by cmoura-p          #+#    #+#              #
#    Updated: 2025/01/22 20:16:43 by cmoura-p         ###   ########.fr        #
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
			src/init/utils_init.c \
			src/init/utils_envp.c \
			src/run.c \
			src/clear/free_funcs.c \
			src/tokenizer/tokenizer.c \
			src/tokenizer/tokenizer_quotes.c \
			src/tokenizer/tokenizer_metachar.c \
			src/tokenizer/tokenizer_redir.c \
			src/tokenizer/tokenizer_word.c \
			src/tokenizer/utils_tokenizer.c \
			src/tokenizer/token_prints.c \
			src/parser/parsing.c \
			src/parser/parser_expand.c \
			src/parser/parser_redir.c \
			src/parser/parser_organizing.c \
			src/parser/utils_expand.c \
			src/parser/utils_parsing.c

OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

VALGRIND_FLAGS = 	--quiet --leak-check=full --show-leak-kinds=all --track-fds=yes \
					--trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $@ $(OBJS) $(LIBFT) $(READLINE_FLAG)

# Regra para compilar arquivos fonte em arquivos objeto
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)/src/init $(OBJ_DIR)/src/clear $(OBJ_DIR)/src/parser \
						$(OBJ_DIR)/src/tokenizer
	@$(CC) $(CFLAGS) -c $< -o $@

# Regras para criar subdiretórios necessários no OBJ_DIR
$(OBJ_DIR)/src/init:
	@mkdir -p $@

$(OBJ_DIR)/src/clear:
	@mkdir -p $@

$(OBJ_DIR)/src/tokenizer:
	@mkdir -p $@

$(OBJ_DIR)/src/parser:
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT):
	@make -C $(LIBFT_DIR) -s

valgrind: all
	@echo "Executando Valgrind com:"
	@echo "FLAGS: $(VALGRIND_FLAGS)"
	@echo "SUPPRESSIONS: $(VALGRIND_SUPP)"
	@echo "BINÁRIO: ./$(NAME)"
	valgrind $(VALGRIND_FLAGS) $(VALGRIND_SUPP) ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) -s

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) -s

re: fclean all

.PHONY: all clean fclean re

