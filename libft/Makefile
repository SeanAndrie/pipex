# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/25 18:51:11 by sgadinga          #+#    #+#              #
#    Updated: 2025/03/31 16:11:29 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC_DIR = src
OBJ_DIR = obj
GNL_DIR = $(SRC_DIR)/get_next_line
PRINTF_DIR = $(SRC_DIR)/ft_printf

GNL_UTILS = $(GNL_DIR)/get_next_line_utils.c
PRINTF_UTILS = $(addprefix $(PRINTF_DIR)/, \
			     ft_format_parsers.c ft_format_spec.c \
				 ft_format_utils.c ft_print_char.c \
				 ft_print_dec_int.c ft_print_hex.c \
			     ft_print_str.c ft_print_uint.c)

SRCS = $(addprefix $(SRC_DIR)/, \
		 ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
	   	 ft_isalpha.c ft_isascii.c ft_isdigit.c \
	   	 ft_isprint.c ft_itoa.c ft_memchr.c ft_split.c \
	   	 ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	   	 ft_putchar_fd.c ft_putendl_fd.c ft_strjoin.c \
	   	 ft_putnbr_fd.c ft_putstr_fd.c ft_striteri.c\
	   	 ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
	   	 ft_strlen.c ft_strmapi.c ft_strncmp.c \
	   	 ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	   	 ft_substr.c ft_tolower.c ft_toupper.c \
	   	 ft_printf.c get_next_line.c) $(PRINTF_UTILS) $(GNL_UTILS)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re