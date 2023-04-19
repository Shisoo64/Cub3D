# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2023/04/19 18:02:44 by bchabot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS =	src/main.c \
		src/input_manager.c \
		src/movement.c \
		src/initialize.c \
		src/parsing.c \
		src/rendering.c \
		src/map.c \
		src/free.c \
		src/error.c \
		src/assets.c \
		src/utils_parsing.c \
		src/utils_mlx.c \
		src/utils_rendering.c \
		src/utils_map.c

SRCS_BONUS =	src_bonus/main.c \
				src_bonus/input_manager.c \
				src_bonus/foot_movement.c \
				src_bonus/bike_movement.c \
				src_bonus/sprites.c \
				src_bonus/screens.c \
				src_bonus/dialog.c \
				src_bonus/dialog_utils.c \
				src_bonus/utils.c \
				src_bonus/init.c \
				src_bonus/parsing.c \
				src_bonus/check_map.c \
				src_bonus/map_check_assets.c \
				src_bonus/map_fill_assets.c \
				src_bonus/parsing_utils.c \
				src_bonus/minimap.c \
				src_bonus/raycaster.c \
				src_bonus/rendering_controller.c \
				src_bonus/rendering_outside.c \
				src_bonus/rendering_inside.c \
				src_bonus/map.c \
				src_bonus/free.c \
				src_bonus/error.c

CC = @clang

LIBFT = libft/libft.a

MLX = mlx_linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g3

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : message $(NAME)
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


bonus : logo $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)
	@echo "\e[1A\e[2K\e[1A\e[2K\e[1A\e[2K\e[1A\e[2K\e[1;32m📦 Grand Theft Moto compiled!\n\033[0m"



logo :
	@echo "     \e[1;34m  _____               _  \e[0m"
	@echo "     \e[1;34m |   __|___ ___ ___ _| | \e[0m"
	@echo "     \e[1;34m |  |  |  _| .'|   | . | \e[0m"
	@echo "     \e[1;34m |_____|_|_|__,|_|_|___|_\e[0m"
	@echo "         \e[1;34m |_   _| |_ ___|  _| |_ \e[0m"
	@echo "         \e[1;34m   | | |   | -_|  _|  _|\e[0m"
	@echo "         \e[1;34m___|_| |_|_|___|_| |_|  \e[0m"
	@echo "       \e[1;34m |     |___| |_ ___  \e[0m"
	@echo "       \e[1;34m | | | | . |  _| . | \e[0m"
	@echo "       \e[1;34m |_|_|_|___|_| |___| \e[0m\n\n\n\n"

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
