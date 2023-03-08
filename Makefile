# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2023/03/08 03:23:33 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS =	src/main.c \
		src/input_manager.c \
		src/foot_movement.c \
		src/bike_movement.c \
		src/utils.c \
		src/parsing.c \
		src/map.c \
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
	@echo "\e[1A\e[2K\e[1A\e[2K"

%.o : %.c
	@echo "\e[1A\e[2K\e[1mCompiling $<\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make -sC libft/

$(MLX) :
	@make -sC mlx_linux/

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)
	@echo "\e[1A\e[2K\e[1A\e[2K\e[1A\e[2K\e[1A\e[2K\e[1;32m📦 $(NAME) compiled!\n\n\033[0m"


bonus : $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

logo :
	@echo "      \e[1;44m  _____               _  \e[0m           "
	@echo "      \e[1;44m |   __|___ ___ ___ _| | \e[0m           "
	@echo "      \e[1;44m |  |  |  _| .'|   | . | \e[0m           "
	@echo "      \e[1;44m |_____|_|_|__,|_|_|___|_\e[0m           "
	@echo "          \e[1;44m |_   _| |_ ___|  _| |_ \e[0m"
	@echo "          \e[1;44m   | | |   | -_|  _|  _|\e[0m"
	@echo "          \e[1;44m___|_| |_|_|___|_| |_|  \e[0m"
	@echo "        \e[1;44m |     |___| |_ ___  \e[0m"
	@echo "        \e[1;44m | | | | . |  _| . | \e[0m"
	@echo "        \e[1;44m |_|_|_|___|_| |___| \e[0m\n"
#	@echo "\e[1;44m                                          \e[0m"
	@echo "\e[1;34;107m    __  ___                    _  __ _    \e[0m"
	@echo "\e[1;34;107m   /  |/  /___  _____________ (_)/ / /__  \e[0m"
	@echo "\e[1;34;107m  / /|_/ / __ \\/ ___/ ___/ _ \\/ / / / _ \\ \e[0m"
	@echo "\e[1;34;107m / /  / / /_/ / /  (__  )  __/ / / /  __/ \e[0m"
	@echo "\e[1;34;107m/_/  /_/\__,_/_/  /____/\___/_/_/_/\___/  \e[0m\n"
                                         

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
	@echo "\e[1A\e[2K\e[91m🧹 Binary files and executable cleaned!\033[0m"

re : fclean all

.PHONY : all re clean fclean logo message