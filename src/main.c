/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 13:57:57 by ccauderl          #+#    #+#             */
/*   Updated: 2026/09/18 21:06:43 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	close_win(t_game *game)
{
	mlx_loop_end(game->mlx);
	free_all(game);
	exit(0);
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

	ft_bzero(&game, sizeof(game));
	game.map_fd = -1;
	if (argc != 2)
		return (print_error(&game, "Wrong number of arguments."), 0);
	init(&game, argv[1]);
	if (open_textures(&game, &game.tex) < 0)
		return (print_error(&game, "Texture opening failed."), 0);
	mlx_hook(game.win, 2, 1 << 0, (int (*)())(void *)key_press, &game);
	mlx_hook(game.win, 17, 1 << 0, (int (*)())(void *)close_win, &game);
	mlx_loop_hook(game.mlx, (int (*)())(void *)rendering, &game);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}
