/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:48:16 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 18:48:17 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	put_pixel(t_data_image *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (0 < x && x < SIZE_WIN_X && 0 < y && y < SIZE_WIN_Y)
	{
		offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
		dst = data->addr + offset;
		*(unsigned int *) dst = color;
	}
}

/*
	Get the color of the pixel [x, y] from the image.
*/
unsigned int	read_pixel(t_data_image *data, int x, int y)
{
	unsigned int	color;
	int				offset;

	color = 0;
	if (0 < x && x < data->width && 0 < y && y < data->height)
	{
		offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
		color = *(unsigned int *)(data->addr + offset);
	}
	return (color);
}
