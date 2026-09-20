/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:08:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	store_colour(char **split, t_game *game, const char *id)
{
	if (ft_strcmp(id, "C") == 0)
	{
		game->map.ceiling_colour[0] = ft_atoi(split[0]);
		game->map.ceiling_colour[1] = ft_atoi(split[1]);
		game->map.ceiling_colour[2] = ft_atoi(split[2]);
		game->map.ceiling_colour[3] = 0;
		game->map.ceiling_set = 1;
	}
	else if (ft_strcmp(id, "F") == 0)
	{
		game->map.floor_colour[0] = ft_atoi(split[0]);
		game->map.floor_colour[1] = ft_atoi(split[1]);
		game->map.floor_colour[2] = ft_atoi(split[2]);
		game->map.floor_colour[3] = 0;
		game->map.floor_set = 1;
	}
}

static void	free_split_data(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_colours(const char *line, t_game *game, const char *ID)
{
	char	**split;
	char	*trimmed;

	trimmed = ft_strtrim(ft_strstr(line, ID) + 1, " \t\n");
	if (!trimmed)
		print_error(game, "Cannot read colour definition.");
	split = ft_split(trimmed, ',');
	if (!split)
		print_error(game, "Cannot allocate colour definition.");
	if (!split[0] || !split[1] || !split[2] || split[3])
		print_error(game, "Colour must contain exactly three values: R,G,B.");
	store_colour(split, game, ID);
	free_split_data(split);
	free(trimmed);
	check_colour(game);
}

void	check_colour(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->map.floor_colour[i] < 0 || game->map.floor_colour[i] > 255)
			print_error(game, "Floor colour values must be between 0 and 255.");
		else if (game->map.ceiling_colour[i] < 0)
			print_error(game,
				"Ceiling colour values must be between 0 and 255.");
		else if (game->map.ceiling_colour[i] > 255)
			print_error(game,
				"Ceiling colour values must be between 0 and 255.");
		i++;
	}
}
