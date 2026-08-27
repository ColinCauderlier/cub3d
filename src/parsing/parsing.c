/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:34:02 by lucinguy          #+#    #+#             */
/*   Updated: 2026/08/24 22:54:58 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	**open_file(char *filename, t_game game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line == "\n")
			continue ;
		got_paths(line, game);
		got_colours(line, game);
		line = get_next_line(fd);
		if (all_set(game) == 1)
			break ;
	}
	while (line && line == "\n") // on saute les retours a la ligne
		line = get_next_line(fd);
	if (line == NULL) // pas de map ou pas tout set up a la fin du fichier
		perror("Misconfiguration found in the map");
	map_copy(fd, game);
}

void	map_copy(int fd, t_game game)
{
	char	*line;
	int		i;
	int		len;

	i = 1;
	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		game.map.map_plan = malloc(sizeof(char *) * i);
		if (!game.map.map_plan)
			perror("Map malloc has failed");
		game.map.map_plan[i - 1] = malloc(sizeof(char) * ft_strlen(line));
		if (!game.map.map_plan[i - 1])
			perror("Map malloc has failed");
		ft_strlcpy(game.map.map_plan[i - 1], line, len - 1);
		i++;
		line = get_next_line(fd);
	}
}

void	got_colours(char *line, t_game game)
{
	if (ft_strstr(line, "F"))
	{
		if (game.map.floor_colour[0])
			perror("Misconfiguration found in the map");
		init_colours(line, game, "F");
	}
	else if (ft_strstr(line, "C"))
	{
		if (game.map.ceiling_colour[0])
			perror("Misconfiguration found in the map");
		init_colours(line, game, "C");
	}
}

void	got_paths(char *line, t_game game)
{
	if (ft_strstr(line, "NO"))
	{
		if (game.map.NO_path)
			perror("Misconfiguration found in the map");
		init_paths(line, game, "NO");
	}
	else if (ft_strstr(line, "SO"))
	{
		if (game.map.SO_path)
			perror("Misconfiguration found in the map");
		init_paths(line, game, "SO");
	}
	else if (ft_strstr(line, "WE"))
	{
		if (game.map.WE_path)
			perror("Misconfiguration found in the map");
		init_paths(line, game, "WE");
	}
	else if (ft_strstr(line, "EA"))
	{
		if (game.map.EA_path)
			perror("Misconfiguration found in the map");
		init_paths(line, game, "EA");
	}
}
