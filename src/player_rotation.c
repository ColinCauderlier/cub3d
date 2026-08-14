/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:47:28 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 18:47:53 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate_right(t_game *game)
{
	rotate(game->player.dir, NULL, to_rad(PLAYER_ROTATION));
	rotate(game->player.dir, game->player.plan, to_rad(90));
	create_new_image(game);
	rendering(game);
}

void	rotate_left(t_game *game)
{
	rotate(game->player.dir, NULL, (to_rad(-1 * PLAYER_ROTATION)));
	rotate(game->player.dir, game->player.plan, to_rad(90));
	create_new_image(game);
	rendering(game);
}
