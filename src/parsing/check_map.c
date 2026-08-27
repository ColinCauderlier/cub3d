/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:18:44 by lucinguy          #+#    #+#             */
/*   Updated: 2026/08/24 23:16:33 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

// Check allowed char in map
int	is_allowed(char c)
{
	if (c != '0' || c != '1' || c != 'N' || c != 'S' || c != 'E' || c != 'W')
		return (1);
	return (0);
}

// Check file format
int	is_cub_file(const char *mapname)
{
	int	len;

	if (!mapname)
		return (1);
	if (ft_strncmp(mapname + len - 4, ".cub", 4) != NULL)
		return (0);
	return (1);
}

// Count spawn points
int	count_spawn(char **map_plan, t_map map)
{
	int i = 0;
	int j = 0;
	while (map_plan[i])
	{
		if (map_plan[i] == 'N' || map_plan[i] == 'S' || map_plan[i] == 'E' || map_plan[i] == 'W')
			map.spawn_number++;
		i++;
	}
	if (map.spawn_number != 1)
		return 1;
	return 0;
}
