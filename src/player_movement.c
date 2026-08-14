/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:40:21 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 18:43:40 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	create_new_image(t_game *game)
{
	mlx_destroy_image(game->mlx, game->data_img.img);
	game->data_img.img = mlx_new_image(game->mlx, SIZE_WIN_X, SIZE_WIN_Y);
	game->data_img.addr = mlx_get_data_addr(game->data_img.img,
			&game->data_img.bits_per_pixel, &game->data_img.line_length,
			&game->data_img.endian);
}

void	move_forward(t_game *game)
{
	double	next_x_pos;
	double	next_y_pos;

	next_x_pos = game->player.pos[X] + PLAYER_SPEED * game->player.dir[X];
	next_y_pos = game->player.pos[Y] + PLAYER_SPEED * game->player.dir[Y];
	if (game->map[(int)floor(next_y_pos)][(int)floor(next_x_pos)] != 1)
	{
		game->player.pos[X] = next_x_pos;
		game->player.pos[Y] = next_y_pos;
		create_new_image(game);
		rendering(game);
	}
}

void	move_backward(t_game *game)
{
	double	next_x_pos;
	double	next_y_pos;

	next_x_pos = game->player.pos[X] - PLAYER_SPEED * game->player.dir[X];
	next_y_pos = game->player.pos[Y] - PLAYER_SPEED * game->player.dir[Y];
	if (game->map[(int)floor(next_y_pos)][(int)floor(next_x_pos)] != 1)
	{
		game->player.pos[X] = next_x_pos;
		game->player.pos[Y] = next_y_pos;
		create_new_image(game);
		rendering(game);
	}
}

void	move_left(t_game *game)
{
	double	next_x_pos;
	double	next_y_pos;

	next_x_pos = game->player.pos[X] - PLAYER_SPEED * game->player.plan[X];
	next_y_pos = game->player.pos[Y] - PLAYER_SPEED * game->player.plan[Y];
	if (game->map[(int)floor(next_y_pos)][(int)floor(next_x_pos)] != 1)
	{
		game->player.pos[X] = next_x_pos;
		game->player.pos[Y] = next_y_pos;
		create_new_image(game);
		rendering(game);
	}
}

void	move_right(t_game *game)
{
	double	next_x_pos;
	double	next_y_pos;

	next_x_pos = game->player.pos[X] + PLAYER_SPEED * game->player.plan[X];
	next_y_pos = game->player.pos[Y] + PLAYER_SPEED * game->player.plan[Y];
	if (game->map[(int)floor(next_y_pos)][(int)floor(next_x_pos)] != 1)
	{
		game->player.pos[X] = next_x_pos;
		game->player.pos[Y] = next_y_pos;
		create_new_image(game);
		rendering(game);
	}
}
