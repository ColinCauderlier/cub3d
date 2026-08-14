/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:44:21 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 19:39:09 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
	Destroy texture images from index 0 to i. 
*/
static void	destroy_previous_images(t_game *game, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		mlx_destroy_image(game->mlx, game->tex.tex_img[j].img);
		j++;
	}
}

/*
    Create the texture images.
    If an error occurs, destroy every texture images 
    and return the opposite of the name index (from -4 to -1).
*/
int	open_textures(t_game *game, t_tex *tex)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tex->tex_img[i].img = mlx_xpm_file_to_image(game->mlx,
				tex->tex_names[i],
				&tex->tex_img[i].width,
				&tex->tex_img[i].height);
		if (!game->tex.tex_img[i].img)
		{
			destroy_previous_images(game, i);
			return ((-1 * i) - 1);
		}
		tex->tex_img[i].addr = mlx_get_data_addr(tex->tex_img[i].img,
				&tex->tex_img[i].bits_per_pixel,
				&tex->tex_img[i].line_length,
				&tex->tex_img[i].endian);
		i++;
	}
	return (0);
}

/*
	Destroy all texture images.
*/
void	close_textures(t_game *game)
{
	int	img_index;

	img_index = 0;
	while (img_index < 4)
	{
		mlx_destroy_image(game->mlx, game->tex.tex_img[img_index].img);
		img_index++;
	}
}
