/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 14:49:17 by ccauderl          #+#    #+#             */
/*   Updated: 2026/09/18 21:06:43 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SIZE_WIN_X, SIZE_WIN_Y, "cub3D");
	game->data_img.img = mlx_new_image(game->mlx, SIZE_WIN_X, SIZE_WIN_Y);
	game->data_img.line_length = 20;
	game->data_img.addr = mlx_get_data_addr(game->data_img.img,
			&game->data_img.bits_per_pixel, &game->data_img.line_length,
			&game->data_img.endian);
}

/*
	Initialize the player coordinates and camera direction
*/
static void	init_player(t_game *game)
{
	rotate(game->player.dir, game->player.plan, to_rad(90));
	game->player.plan[X] *= tanf(to_rad(FOV / 2));
	game->player.plan[Y] *= tanf(to_rad(FOV / 2));
}

void	init_position(t_game *game, int x, int y, char dir)
{
	game->player.pos[X] = x + 0.5;
	game->player.pos[Y] = y + 0.5;
	game->map.map_plan[y][x] = '0';
	if (dir == 'S')
	{
		game->player.dir[X] = 0.0;
		game->player.dir[Y] = 1.0;
	}
	else if (dir == 'E')
	{
		game->player.dir[X] = 1.0;
		game->player.dir[Y] = 0.0;
	}
	else if (dir == 'W')
	{
		game->player.dir[X] = -1.0;
		game->player.dir[Y] = 0.0;
	}
	else if (dir == 'N')
	{
		game->player.dir[X] = 0.0;
		game->player.dir[Y] = -1.0;
	}
}

void	init(t_game *game, char *mapname)
{
	ft_bzero(game, sizeof(*game));
	game->map_fd = -1;
	init_map(game, mapname);
	init_mlx(game);
	init_player(game);
}
