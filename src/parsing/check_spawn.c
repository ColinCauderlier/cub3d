/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:06:43 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	count_spawn_line(const char *line)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
			count++;
		j++;
	}
	return (count);
}

int	count_spawn(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map_plan[i])
	{
		game->map.spawn_number += count_spawn_line(game->map.map_plan[i]);
		i++;
	}
	if (game->map.spawn_number > 1)
		print_error(game, "Multiple spawns found in map.");
	if (game->map.spawn_number < 1)
		print_error(game, "No spawn found in map.");
	return (0);
}
