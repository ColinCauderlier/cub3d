/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 17:06:21 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/14 17:44:09 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
    Get the size of the projected wall from the ray length (wall_dist).
*/
static void	get_wall_size(t_raycast *ray)
{
	if (ray->side == X)
		ray->wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
	ray->wall_height = (int)(SIZE_WIN_Y / (ray->wall_dist + EPSILON));
	ray->draw_wall[START] = (SIZE_WIN_Y - ray->wall_height) / 2;
	if (ray->draw_wall[START] < 0)
		ray->draw_wall[START] = 0;
	ray->draw_wall[END] = (SIZE_WIN_Y + ray->wall_height) / 2;
	if (ray->draw_wall[END] >= SIZE_WIN_Y)
		ray->draw_wall[END] = SIZE_WIN_Y - 1;
}

//DDA: Digital Differential Analysis algorithm
static void	dda(t_game *game, t_raycast *ray)
{
	while (ray->hit == FALSE)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map[X] += ray->step[X];
			ray->side = X;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map[Y] += ray->step[Y];
			ray->side = Y;
		}
		if (game->map[ray->map[Y]][ray->map[X]] == 1)
			ray->hit = TRUE;
	}
}

static void	calculate_step_and_sidedist(t_player *plyr, t_raycast *ray)
{
	if (ray->ray_dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = plyr->pos[X] - ray->map[X];
		ray->side_dist[X] *= ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = ray->map[X] - plyr->pos[X] + 1;
		ray->side_dist[X] *= ray->delta_dist[X];
	}
	if (ray->ray_dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = plyr->pos[Y] - ray->map[Y];
		ray->side_dist[Y] *= ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = ray->map[Y] - plyr->pos[Y] + 1;
		ray->side_dist[Y] *= ray->delta_dist[Y];
	}
}

/*
    sideDist are the distances the ray has to travel 
	from its start position to the first x-side and the first y-side. 
    
	deltaDist are the distances the ray has to travel to go 
	from a side to the next.
    
	perpWallDist is used to calculate the length of the ray 
	from the camera plane to the wall.
*/
void	raycast(t_game *game, t_player *plyr, t_raycast *ray)
{
	ray->hit = FALSE;
	if (ray->ray_dir[X] == 0)
		ray->delta_dist[X] = INFINITY;
	else
		ray->delta_dist[X] = fabs(1 / ray->ray_dir[X]);
	if (ray->ray_dir[Y] == 0)
		ray->delta_dist[Y] = INFINITY;
	else
		ray->delta_dist[Y] = fabs(1 / ray->ray_dir[Y]);
	calculate_step_and_sidedist(plyr, ray);
	dda(game, ray);
	get_wall_size(ray);
}
