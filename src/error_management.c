/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 11:48:08 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:11:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	destroy_mlx(t_game *game)
{
	close_textures(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->data_img.img)
	{
		mlx_destroy_image(game->mlx, game->data_img.img);
		game->data_img.img = NULL;
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	if (game->map_fd >= 0)
	{
		drain_gnl(game->map_fd);
		close(game->map_fd);
		game->map_fd = -1;
	}
	free(game->parse_line);
	game->parse_line = NULL;
	if (game->mlx)
		destroy_mlx(game);
	free_map_plan(game);
	free_int_map(game);
	free_texture_paths(game);
}

int	print_error(t_game *game, char *error_message)
{
	ft_fprintf(2, "Error\n%s\n", error_message);
	free_all(game);
	exit(EXIT_FAILURE);
}
