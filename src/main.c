/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 13:57:57 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 19:39:44 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	map[10][24] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static void	free_all(t_game *game)
{
	mlx_destroy_image(game->mlx, game->data_img.img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

static int	close_win(t_game *game)
{
	mlx_loop_end(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	free_all(game);
	exit(0);
	return (0);
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEYCODE_ESC)
		close_win(game);
	if (keycode == KEYCODE_W)
		move_forward(game);
	if (keycode == KEYCODE_S)
		move_backward(game);
	if (keycode == KEYCODE_A)
		move_left(game);
	if (keycode == KEYCODE_D)
		move_right(game);
	if (keycode == KEYCODE_LEFTARROW)
		rotate_left(game);
	if (keycode == KEYCODE_RIGHTARROW)
		rotate_right(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = map;
	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Wrong number of arguments\n");
		return (0);
	}
	ft_fprintf(STDOUT_FILENO, "%s\n", argv[1]);
	init(&game);
	if (open_textures(&game, &game.tex) < 0)
	{
		ft_fprintf(STDERR_FILENO, "Error while opening the texture files\n");
		return (-1);
	}
	mlx_hook(game.win, 2, 1 << 0, (int (*)())(void *)key_press, &game);
	mlx_hook(game.win, 17, 1 << 0, (int (*)())(void *)close_win, &game);
	mlx_loop_hook(game.mlx, (int (*)())(void *)rendering, &game);
	mlx_loop(game.mlx);
	close_textures(&game);
	return (0);
}
