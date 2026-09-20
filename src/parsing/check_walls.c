/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 11:56:52 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:11:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	is_void_at(const t_fill *fill, int x, int y)
{
	if (y < 0 || y >= fill->height || !fill->game.map.map_plan[y] || x < 0
		|| x >= (int)ft_strlen(fill->game.map.map_plan[y]))
		return (1);
	return (fill->game.map.map_plan[y][x] == ' '
		|| fill->game.map.map_plan[y][x] == '\t'
		|| fill->game.map.map_plan[y][x] == '\v');
}

static void	flood_fill(t_fill *fill, int x, int y)
{
	if (x < 0 || x >= fill->width + 2 || y < 0 || y >= fill->height + 2
		|| fill->visited[y][x] || !is_void_at(fill, x - 1, y - 1))
		return ;
	fill->visited[y][x] = 1;
	flood_fill(fill, x + 1, y);
	flood_fill(fill, x - 1, y);
	flood_fill(fill, x, y + 1);
	flood_fill(fill, x, y - 1);
}

static int	check_floor(t_fill *fill)
{
	int	i;
	int	j;

	i = 0;
	while (i < fill->height)
	{
		j = 0;
		while (fill->game.map.map_plan[i][j])
		{
			if (fill->game.map.map_plan[i][j] != '1' && !is_void_at(fill, j, i)
				&& ((is_void_at(fill, j + 1, i) && fill->visited[i + 1][j + 2])
					|| (is_void_at(fill, j - 1, i) && fill->visited[i + 1][j])
					|| (is_void_at(fill, j, i + 1) && fill->visited[i + 2][j
						+ 1]) || (is_void_at(fill, j, i - 1)
						&& fill->visited[i][j + 1])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	init_fill(t_fill *fill, t_game game)
{
	int	i;

	fill->game = game;
	fill->visited = ft_calloc(fill->height + 2, sizeof(char *));
	if (!fill->visited)
		print_error(&fill->game, "Map malloc has failed.");
	i = 0;
	while (i < fill->height + 2)
	{
		fill->visited[i] = ft_calloc(fill->width + 2, sizeof(char));
		if (!fill->visited[i])
		{
			while (i > 0)
				free(fill->visited[--i]);
			free(fill->visited);
			print_error(&fill->game, "Map malloc has failed.");
		}
		i++;
	}
}

void	check_walls(t_game game)
{
	t_fill	fill;
	int		line_width;

	fill.width = 0;
	fill.height = 0;
	while (game.map.map_plan[fill.height])
	{
		line_width = ft_strlen(game.map.map_plan[fill.height]);
		if (line_width > fill.width)
			fill.width = line_width;
		fill.height++;
	}
	init_fill(&fill, game);
	flood_fill(&fill, 0, 0);
	if (!check_floor(&fill))
	{
		free_visited(&fill);
		print_error(&fill.game, "Map must be surrounded by walls.");
	}
	free_visited(&fill);
}
