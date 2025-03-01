# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 20:20:52 by joseoliv          #+#    #+#              #
#    Updated: 2025/03/01 18:24:56 by cmoura-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = char/ft_isalpha.c char/ft_isdigit.c char/ft_isalnum.c char/ft_toupper.c\
	input_output/ft_putstr_fd.c input_output/ft_printf/ft_printf.c \
	input_output/ft_printf/write_funcs.c input_output/ft_printf/nbr_funcs.c \
	memory/ft_bzero.c memory/ft_calloc.c memory/ft_memset.c \
	string/ft_split.c string/ft_strchr.c string/ft_strdup.c string/ft_strjoin.c \
	string/ft_strlcpy.c string/ft_strlen.c string/ft_strncmp.c string/ft_substr.c \
	string/ft_strcmp.c string/ft_strcpy.c \
	utility/ft_atoi_int.c utility/ft_itoa.c utility/ft_pow.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
