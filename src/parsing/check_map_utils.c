/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 17:50:07 by lucinguy          #+#    #+#             */
/*   Updated: 2026/09/18 21:11:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

// Check allowed char in map
int	is_allowed(char c)
{
	return (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != '\n');
}

void	skip_empty_lines(int fd, char **line)
{
	char	*next_line;

	while (*line && (*line)[0] == '\n')
	{
		next_line = get_next_line(fd);
		free(*line);
		*line = next_line;
	}
}

// Check file format
void	is_cub_file(const char *mapname, t_game *game)
{
	int	len;

	len = ft_strlen(mapname);
	if (!mapname)
		print_error(game, "File map must have a name.");
	if (len < 4 || ft_strncmp(mapname + len - 4, ".cub", 4) != 0)
		print_error(game, "File map must be in .cub format.");
}

int	is_wall(const t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.counted_lines || !game->map.int_map
		|| !game->map.map_plan || !game->map.map_plan[y] || x < 0
		|| x >= (int)ft_strlen(game->map.map_plan[y]))
		return (1);
	return (game->map.int_map[y][x] == 1);
}
