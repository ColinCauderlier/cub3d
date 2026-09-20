/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 18:15:42 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:11:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	count_lines(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

void	copy_map_line(const char *line, t_game *game, int i)
{
	int	len;

	len = ft_strlen(line);
	game->map.map_plan[i] = malloc(sizeof(char) * (len + 1));
	if (!game->map.map_plan[i])
		print_error(game, "Map malloc has failed.");
	ft_strlcpy(game->map.map_plan[i], line, len + 1);
	if (len > 0 && game->map.map_plan[i][len - 1] == '\n')
		game->map.map_plan[i][len - 1] = '\0';
}

void	free_visited(t_fill *fill)
{
	int	i;

	i = 0;
	while (i < fill->height + 2)
		free(fill->visited[i++]);
	free(fill->visited);
}

void	init_paths(const char *line, t_game *game, const char *ID)
{
	char	*trimmed;

	trimmed = ft_strtrim(ft_strstr(line, ID) + 2, " \t\n");
	if (!trimmed)
		print_error(game, "Texture path is missing.");
	if (ft_strcmp(ID, "NO") == 0)
		game->tex.tex_names[0] = ft_strdup(trimmed);
	else if (ft_strcmp(ID, "SO") == 0)
		game->tex.tex_names[1] = ft_strdup(trimmed);
	else if (ft_strcmp(ID, "WE") == 0)
		game->tex.tex_names[3] = ft_strdup(trimmed);
	else if (ft_strcmp(ID, "EA") == 0)
		game->tex.tex_names[2] = ft_strdup(trimmed);
	free(trimmed);
}

int	all_set(const t_game *game)
{
	if (!game->map.floor_set || !game->map.ceiling_set)
		return (0);
	if (game->map.spawn_number > 1)
		return (0);
	if (!game->tex.tex_names[0] || !game->tex.tex_names[1]
		|| !game->tex.tex_names[2] || !game->tex.tex_names[3])
		return (0);
	return (1);
}
