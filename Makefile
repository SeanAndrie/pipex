# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 16:19:12 by sgadinga          #+#    #+#              #
#    Updated: 2025/04/15 13:39:04 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BNAME = pipex_bonus
CC = cc 
CFLAGS = -Wall -Werror -Wextra -Ilibft/includes -Iincludes

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, \
		 pipex.c pipex_utils.c path_utils.c cmd_ops.c exec.c)
BSRCS = $(addprefix $(SRC_DIR)/, \
		  pipex_bonus.c pipex_utils_bonus.c path_utils.c cmd_ops.c exec.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BOBJS = $(BSRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libft $(NAME)
bonus: libft $(BNAME)

libft: 
	@make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

$(BNAME): $(BOBJS)
	$(CC) $(CFLAGS) -o $(BNAME) $(BOBJS) -Llibft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft