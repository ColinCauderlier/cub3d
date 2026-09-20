# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/08 14:23:37 by ccauderl          #+#    #+#              #
#    Updated: 2026/09/16 21:03:34 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
MLXFLAGS1		:= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux
MLXFLAGS2		:=  -lXext -lX11 -lm -lz
RM		:= rm -rf
INCS		:= -I ./includes -I ./libft -I ./libft/ft_printf -I ./libft/ft_fprintf -I ./libft/gnl
LIBFT_DIR	:= libft
SRCS_DIR	:= src
OBJS_DIR	:= objs/cub3D
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

.SILENT:

SRCS		:= main.c \
			init.c \
			utils.c \
			movement/player_movement.c \
			movement/player_rotation.c \
			parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/colour_utils.c \
			cleanup.c \
			parsing/check_map.c \
			parsing/check_spawn.c \
			parsing/check_map_utils.c \
			render/textures.c \
			render/raycasting.c \
			render/rendering.c \
			render/put_pixel.c \
			error_management.c \
			parsing/check_walls.c

SRCS_FILES	:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		:= $(SRCS_FILES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT_LIB) $(MLXFLAGS1) $(MLXFLAGS2) -o $(NAME)
	@echo "✓ $(NAME) compiled successfully!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) -s clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s fclean -C $(LIBFT_DIR)
	$(MAKE) -s fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
