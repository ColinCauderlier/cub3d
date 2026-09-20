/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:18:44 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:12:05 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	map_to_int(t_game *game);
static void	map_line_to_int(t_game *game, int i);
static void	check_line(t_game *game, int i);

void	init_map(t_game *game, const char *map_name)
{
	is_cub_file(map_name, game);
	if (open_file(map_name, game) < 0)
		return ;
	game->map.int_map = ft_calloc(game->map.counted_lines + 1, sizeof(int *));
	if (!game->map.int_map)
		print_error(game, "Map malloc has failed.");
	map_check(game);
}

void	map_check(t_game *game)
{
	int	i;

	i = 0;
	count_spawn(game);
	while (game->map.map_plan[i])
	{
		check_line(game, i);
		i++;
	}
	map_to_int(game);
	check_walls(*game);
}

static void	check_line(t_game *game, int i)
{
	int	j;

	j = 0;
	while (game->map.map_plan[i][j])
	{
		if (is_allowed(game->map.map_plan[i][j]) == 1
			|| game->map.map_plan[i][0] == '\n')
			print_error(game,
				"Invalid character in map: use 0, 1, N, S, E,"
				" W.");
		if (game->map.map_plan[i][j] == 'S' || game->map.map_plan[i][j] == 'N'
			|| game->map.map_plan[i][j] == 'E'
			|| game->map.map_plan[i][j] == 'W')
			init_position(game, j, i, game->map.map_plan[i][j]);
		j++;
	}
}

static void	map_to_int(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map_plan[i])
	{
		map_line_to_int(game, i);
		i++;
	}
	game->map.int_map[i] = NULL;
}

static void	map_line_to_int(t_game *game, int i)
{
	int	j;
	int	len;

	len = ft_strlen(game->map.map_plan[i]);
	j = 0;
	game->map.int_map[i] = malloc(sizeof(int) * (len + 1));
	if (!game->map.int_map[i])
		print_error(game, "Map malloc has failed.");
	while (game->map.map_plan[i][j])
	{
		if (game->map.map_plan[i][j] == '1')
			game->map.int_map[i][j] = 1;
		else
			game->map.int_map[i][j] = 0;
		j++;
	}
	game->map.int_map[i][j] = 0;
}
