# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 21:43:02 by cmoura-p          #+#    #+#              #
#    Updated: 2025/04/05 18:00:57 by breda-si         ###   ########.fr        #
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
			src/init/load_export.c \
			src/run.c \
			src/clear/free_funcs_b.c \
			src/clear/free_funcs_c.c \
			src/clear/free_funcs_o.c \
			src/tokenizer/tokenizer.c \
			src/tokenizer/token_prints.c \
			src/tokenizer/tokenizer_quotes.c \
			src/tokenizer/tokenizer_metachar.c \
			src/tokenizer/tokenizer_heredoc.c \
			src/tokenizer/tokenizer_redir.c \
			src/tokenizer/tokenizer_word.c \
			src/tokenizer/utils_tokenizer.c \
			src/parser/parsing.c \
			src/parser/parser_expand.c \
			src/parser/parser_redir.c \
			src/parser/parser_organizing.c \
			src/parser/parser_special.c \
			src/parser/utils_expand.c \
			src/parser/utils_parsing.c \
			src/heredoc/heredoc.c \
			src/heredoc/utils_heredoc.c \
			src/heredoc/heredoc_extra.c \
			src/builtins/cd/cd.c \
			src/builtins/echo/echo.c \
			src/builtins/env/env.c \
			src/builtins/exit/exit.c \
			src/builtins/export/export.c \
			src/builtins/export/insert_expo.c \
			src/builtins/pwd/pwd.c \
			src/builtins/unset/unset.c \
			src/builtins/ft_fprintf.c \
			src/tree/ft_tree.c \
			src/tree/ft_pipe.c \
			src/tree/ft_redir_in.c \
			src/tree/ft_redir_out.c \
			src/tree/ft_redir_app.c \
			src/tree/redir_util.c \
			src/tree/tree_util.c \
			src/tree/duplicate_token_list.c \
			src/execute/ft_env_args.c \
			src/execute/ft_exec_bultins.c \
			src/execute/ft_exec_cmd.c \
			src/execute/ft_exec_pipe.c \
			src/execute/ft_exec_redir.c \
			src/execute/ft_execute.c \
			src/execute/ft_find_path.c \


OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

VALGRIND_FLAGS = 	--quiet --leak-check=full --show-leak-kinds=all --track-fds=yes \
					--trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $@ $(OBJS) $(LIBFT) $(READLINE_FLAG)

# Regra para compilar arquivos fonte em arquivos objeto
$(OBJ_DIR)/%.o: %.c |	$(OBJ_DIR)/src/init $(OBJ_DIR)/src/clear $(OBJ_DIR)/src/parser \
						$(OBJ_DIR)/src/builtins/export $(OBJ_DIR)/src/tokenizer $(OBJ_DIR)/src/heredoc \
						$(OBJ_DIR)/src/builtins/cd $(OBJ_DIR)/src/builtins/echo \
						$(OBJ_DIR)/src/builtins/env $(OBJ_DIR)/src/builtins/exit  \
						$(OBJ_DIR)/src/builtins/pwd $(OBJ_DIR)/src/builtins/unset $(OBJ_DIR) $(OBJ_DIR)/src/tree \
						$(OBJ_DIR)/src/execute
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Regras para criar subdiretórios necessários no OBJ_DIR
$(OBJ_DIR)/src/init:
	@mkdir -p $@

$(OBJ_DIR)/src/clear:
	@mkdir -p $@

$(OBJ_DIR)/src/tokenizer:
	@mkdir -p $@

$(OBJ_DIR)/src/heredoc:
	@mkdir -p $@

$(OBJ_DIR)/src/parser:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/cd:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/echo:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/env:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/exit:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/export:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/pwd:
	@mkdir -p $@

$(OBJ_DIR)/src/builtins/unset:
	@mkdir -p $@

$(OBJ_DIR)/src/tree:
	@mkdir -p $@

$(OBJ_DIR)/src/execute:
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

