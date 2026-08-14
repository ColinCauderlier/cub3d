/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 17:50:29 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/14 17:48:22 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	get_texture_index(const t_raycast *ray)
{
	if (ray->side == Y && ray->ray_dir[Y] > 0)
		return (0);
	else if (ray->side == Y && ray->ray_dir[Y] <= 0)
		return (1);
	else if (ray->side == X && ray->ray_dir[X] <= 0)
		return (2);
	else if (ray->side == X && ray->ray_dir[X] > 0)
		return (3);
	return (0);
}

static void	init_column(t_game *game, t_raycast *ray)
{
	double			wall_x;

	if (ray->side == X)
		wall_x = game->player.pos[Y] + ray->wall_dist * ray->ray_dir[Y];
	else
		wall_x = game->player.pos[X] + ray->wall_dist * ray->ray_dir[X];
	wall_x -= floor(wall_x);
	game->tex.current_tex = game->tex.tex_img[get_texture_index(ray)];
	game->tex.tex_step = 1.0 * game->tex.current_tex.height / ray->wall_height;
	game->tex.tex_pos = ray->draw_wall[START] - SIZE_WIN_Y / 2;
	game->tex.tex_pos += ray->wall_height / 2;
	game->tex.tex_pos *= game->tex.tex_step;
	game->tex.tex_x = (int)(wall_x * game->tex.current_tex.width);
	if (ray->side == X && ray->ray_dir[X] > 0)
		game->tex.tex_x = game->tex.current_tex.width - game->tex.tex_x - 1;
	if (ray->side == 1 && ray->ray_dir[Y] < 0)
		game->tex.tex_x = game->tex.current_tex.width - game->tex.tex_x - 1;
}

static void	draw_column(t_game *game, const t_raycast *ray, t_tex *tex, int column)
{
	int				column_pixel;
	int				color;

	column_pixel = 0;
	while (column_pixel < ray->draw_wall[START])
	{
		put_pixel(&game->data_img, column, column_pixel, BLUE);
		column_pixel++;
	}
	while (column_pixel < ray->draw_wall[END])
	{
		game->tex.tex_y = (int)game->tex.tex_pos;
		color = read_pixel(&tex->current_tex, tex->tex_x, tex->tex_y);
		put_pixel(&game->data_img, column, column_pixel, color);
		column_pixel++;
		game->tex.tex_pos += game->tex.tex_step;
	}
	while (column_pixel < SIZE_WIN_Y)
	{
		put_pixel(&game->data_img, column, column_pixel, DARKGREEN);
		column_pixel++;
	}
}

/*
    screen[X] ∈ [-1, 1] 
    -1 for the left side of the screen and 1 for the right side
*/
void	rendering(t_game *game)
{
	int	column;

	column = 0;
	while (column < SIZE_WIN_X)
	{
		game->ray.map[X] = (int)(game->player.pos[X]);
		game->ray.map[Y] = (int)(game->player.pos[Y]);
		game->ray.screen[X] = (2.0 * column / SIZE_WIN_X) - 1;
		game->ray.ray_dir[X] = game->player.dir[X];
		game->ray.ray_dir[X] += game->player.plan[X] * game->ray.screen[X];
		game->ray.ray_dir[Y] = game->player.dir[Y];
		game->ray.ray_dir[Y] += game->player.plan[Y] * game->ray.screen[X];
		raycast(game, &game->player, &game->ray);
		init_column(game, &game->ray);
		draw_column(game, &game->ray, &game->tex, column);
		column++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->data_img.img, 0, 0);
}
