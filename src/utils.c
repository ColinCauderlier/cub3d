/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 14:56:56 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/13 17:47:52 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
    Rotate src wuth an angle of alpha radians.
    Can be used with and without a destination vector.
*/
void	rotate(double src[2], double dest[2], double alpha)
{
	double	temp[2];

	if (!dest)
	{
		temp[X] = cos(alpha) * src[X] - sin(alpha) * src[Y];
		temp[Y] = sin(alpha) * src[X] + cos(alpha) * src[Y];
		src[X] = temp[X];
		src[Y] = temp[Y];
	}
	else
	{
		dest[X] = cos(alpha) * src[X] - sin(alpha) * src[Y];
		dest[Y] = sin(alpha) * src[X] + cos(alpha) * src[Y];
	}
}

/*
    Convert from degrees to radians
*/
double	to_rad(double alpha)
{
	return (alpha * PI / 180);
}

/*
    Convert from radians to degrees
*/
double	to_deg(double alpha)
{
	return (alpha * 180 / PI);
}

/*
    Convert a RGBA array into hexadecimal
*/
unsigned int	color_to_hex(const int color[4])
{
	unsigned int	result;

	result = color[3];
	result *= 256;
	result += color[0];
	result *= 256;
	result += color[1];
	result *= 256;
	result += color[2];
	result *= 256;
	return (result);
}
