/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/16 21:23:51 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_map_plan(t_game *game)
{
	int	i;

	if (!game->map.map_plan)
		return ;
	i = 0;
	while (game->map.map_plan[i])
	{
		free(game->map.map_plan[i]);
		i++;
	}
	free(game->map.map_plan);
	game->map.map_plan = NULL;
}

void	free_int_map(t_game *game)
{
	int	i;

	if (!game->map.int_map)
		return ;
	i = 0;
	while (game->map.int_map[i])
	{
		free(game->map.int_map[i]);
		i++;
	}
	free(game->map.int_map);
	game->map.int_map = NULL;
}

void	free_texture_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(game->tex.tex_names[i]);
		game->tex.tex_names[i] = NULL;
		i++;
	}
}

void	drain_gnl(int fd)
{
	char	*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
