# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 15:43:34 by sgadinga          #+#    #+#              #
#    Updated: 2025/05/28 16:43:25 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft/includes

SRC_DIR = src
OBJ_DIR = obj

CORE = pipex_utils.c pipex_exec.c command_utils.c debug.c path_utils.c io_handler.c heredoc_utils.c
SRCS = $(addprefix $(SRC_DIR)/, pipex.c $(CORE))
BSRCS = $(addprefix $(SRC_DIR)/, pipex_bonus.c $(CORE))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BOBJS = $(BSRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libft $(NAME)

libft:
	@make -C libft

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

bonus: $(BOBJS) libft
	$(CC) $(CFLAGS) -o $(BONUS) $(BOBJS) -Llibft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft 
