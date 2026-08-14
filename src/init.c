/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 14:49:17 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 19:40:11 by ccauderl         ###   ########.fr       */
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

static void	init_textures(t_game *game)
{
	game->tex.tex_names[0] = "./textures/antoine.xpm";
	game->tex.tex_names[1] = "./textures/antoine_meme.xpm";
	game->tex.tex_names[2] = "./textures/noah.xpm";
	game->tex.tex_names[3] = "./textures/julien.xpm";
}

/*
    Initialize the player coordinates and camera direction
*/
static void	init_player(t_game *game)
{
	game->player.pos[X] = 2.0;
	game->player.pos[Y] = 2.0;
	game->player.dir[X] = 0.0;
	game->player.dir[Y] = 1.0;
	rotate(game->player.dir, game->player.plan, to_rad(90));
	game->player.plan[X] *= tanf(to_rad(FOV / 2));
	game->player.plan[Y] *= tanf(to_rad(FOV / 2));
}

void	init(t_game *game)
{
	init_mlx(game);
	init_textures(game);
	init_player(game);
}
