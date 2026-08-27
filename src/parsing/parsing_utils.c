/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 18:15:42 by lucinguy          #+#    #+#             */
/*   Updated: 2026/08/24 20:38:08 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_paths(char *line, t_game game, char *ID)
{
	line = ft_strstr(line, ID) + 2;
	line = ft_strtrim(line, " ");
	if (ID == "NO")
		game.map.NO_path = line;
	else if (ID == "SO")
		game.map.SO_path = line;
	else if (ID == "WE")
		game.map.WE_path = line;
	else if (ID == "EA")
		game.map.EA_path = line;
	return (line);
}

void	init_colours(char *line, t_game game, char *ID)
{
	line = ft_strstr(line, ID) + 1;
	line = ft_strtrim(line, " ");
	if (ID == "C")
	{
		game.map.ceiling_colour[0] = ft_atoi(ft_split(line, ',')[0]);
		game.map.ceiling_colour[1] = ft_atoi(ft_split(line, ',')[1]);
		game.map.ceiling_colour[2] = ft_atoi(ft_split(line, ',')[2]);
	}
	else if (ID == "F")
	{
		game.map.floor_colour[0] = ft_atoi(ft_split(line, ',')[0]);
		game.map.floor_colour[1] = ft_atoi(ft_split(line, ',')[1]);
		game.map.floor_colour[2] = ft_atoi(ft_split(line, ',')[2]);
	}
	check_colour(game);
	return (line);
}

void	check_colour(t_game game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game.map.floor_colour[i] < 0 || game.map.floor_colour[i] > 255)
			perror("Misconfiguration found in the map");
		if (game.map.ceiling_colour[i] < 0 || game.map.ceiling_colour[i] > 255)
			perror("Misconfiguration found in the map");
		i++;
	}
}

int	all_set(t_game game)
{
	if (!game.map.floor_colour[0] || !game.map.floor_colour[1]
		|| !game.map.floor_colour[2] || !game.map.ceiling_colour[0]
		|| !game.map.ceiling_colour[1] || !game.map.ceiling_colour[2])
		return (0);
	if (game.map.spawn_number > 1)
		return (0);
	if (!game.map.NO_path || !game.map.SO_path || !game.map.WE_path
		|| !game.map.EA_path)
		return (0);
	return (1);
}