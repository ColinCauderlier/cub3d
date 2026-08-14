# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/08 14:23:37 by ccauderl          #+#    #+#              #
#    Updated: 2026/08/08 15:02:54 by ccauderl         ###   ########.fr        #
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

SRCS		:= main.c init.c utils.c rendering.c put_pixel.c player_movement.c player_rotation.c textures.c raycasting.c

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
