# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2023/02/03 23:39:25 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS =	src/main.c \
		src/utils.c \
		src/parsing.c \
		src/map.c \
		src/movement.c \
		src/free.c \
		src/error.c

SRCS_BONUS =	src_bonus/main.c \
				src_bonus/pathfinding.c \
				src_bonus/utils.c \
				src_bonus/utils2.c \
				src_bonus/enemies.c \
				src_bonus/sprites.c \
				src_bonus/map.c \
				src_bonus/free.c \
				src_bonus/error.c \
				src_bonus/anim.c

CC = @clang

LIBFT = libft/libft.a

MLX = mlx_linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g3

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : logo message $(NAME)
	@echo "\e[2A\e[91m                                                                    \033[0m"

%.o : %.c
	@echo "\033[1A\e[1mCompiling $<                                                       \033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make -sC libft/

$(MLX) :
	@make -sC mlx_linux/

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)
	@echo "\e[2A\e[1;32m📦 $(NAME) compiled!                                           \n\n\033[0m"


bonus : $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

logo :
	@echo "\n                          CUB3D                                        "

message:
	@echo "\e[1;5m🗜️  $(NAME) compiling...\n\033[0m"

clean :
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@make -sC libft fclean
	@make -sC mlx_linux clean
	@echo "\033[91m🧹 Binary files cleaned!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\e[1A\e[91m🧹 Binary files and executable cleaned!\033[0m"

re : fclean all

.PHONY : all re clean fclean logo message