/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:34:02 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:11:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	read_config(int fd, char **line, t_game *game)
{
	while (*line)
	{
		if (all_set(game))
			break ;
		got_paths(*line, game);
		got_colours(*line, game);
		free(*line);
		*line = get_next_line(fd);
		game->parse_line = *line;
	}
}

int	open_file(const char *filename, t_game *game)
{
	int		fd;
	char	*line;

	is_cub_file(filename, game);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error(game, "Cannot open map.");
	game->map_fd = fd;
	line = get_next_line(fd);
	game->parse_line = line;
	read_config(fd, &line, game);
	skip_empty_lines(fd, &line);
	game->parse_line = line;
	if (!line)
		print_error(game, "Map data is missing after the configuration.");
	map_copy(line, fd, game, filename);
	drain_gnl(fd);
	close(fd);
	game->map_fd = -1;
	return (0);
}

void	map_copy(char *line, int fd, t_game *game, const char *filename)
{
	int		i;
	char	*next_line;

	i = 0;
	game->map.counted_lines = count_lines(filename);
	game->map.map_plan = ft_calloc(game->map.counted_lines + 1, sizeof(char *));
	if (!game->map.map_plan)
		print_error(game, "Map malloc has failed.");
	while (line && i < game->map.counted_lines && line[0] != '\n')
	{
		copy_map_line(line, game, i);
		i++;
		next_line = get_next_line(fd);
		free(line);
		line = next_line;
		game->parse_line = line;
	}
	game->map.map_plan[i] = NULL;
}

void	got_colours(const char *line, t_game *game)
{
	if (ft_strstr(line, "F"))
	{
		if (game->map.floor_colour[0])
			print_error(game, "Duplicate floor colour definition.");
		init_colours(line, game, "F");
	}
	else if (ft_strstr(line, "C"))
	{
		if (game->map.ceiling_colour[0])
			print_error(game, "Duplicate ceiling colour definition.");
		init_colours(line, game, "C");
	}
}

void	got_paths(const char *line, t_game *game)
{
	if (ft_strstr(line, "NO"))
	{
		if (game->tex.tex_names[0])
			print_error(game, "Duplicate NO texture definition.");
		init_paths(line, game, "NO");
	}
	else if (ft_strstr(line, "SO"))
	{
		if (game->tex.tex_names[1])
			print_error(game, "Duplicate SO texture definition.");
		init_paths(line, game, "SO");
	}
	else if (ft_strstr(line, "WE"))
	{
		if (game->tex.tex_names[3])
			print_error(game, "Duplicate WE texture definition.");
		init_paths(line, game, "WE");
	}
	else if (ft_strstr(line, "EA"))
	{
		if (game->tex.tex_names[2])
			print_error(game, "Duplicate EA texture definition.");
		init_paths(line, game, "EA");
	}
}
