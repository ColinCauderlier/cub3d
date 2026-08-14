/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 13:58:44 by ccauderl          #+#    #+#             */
/*   Updated: 2026/08/14 17:47:51 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//-------CONSTANTS-------//

# define PI 3.14159265358979
# define EPSILON 0.000000001

# define SIZE_WIN_X 1600
# define SIZE_WIN_Y 900

//texture sizes
# define WIDTH  256
# define HEIGHT 256

//FOV and PLAYER_ROTATION are in degrees
# define FOV 90
# define PLAYER_SPEED 0.1
# define PLAYER_ROTATION 10

# define X 0
# define Y 1

# define FALSE 0
# define TRUE 1

# define START 0
# define END 1

# define KEYCODE_ESC 65307
# define KEYCODE_LEFTARROW 65361
# define KEYCODE_UPARROW 65362
# define KEYCODE_RIGHTARROW 65363
# define KEYCODE_DOWNARROW 65364
# define KEYCODE_W 119
# define KEYCODE_A 97
# define KEYCODE_S 115
# define KEYCODE_D 100

# define DARKGREEN 0x00005500
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define ORANGE 0x00FF8000
# define PURPLE 0x00800080
# define TRANSPARENT 0xFF000000

//-------LIBRARIES-------//

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

//-------STRUCTURES-------//

typedef enum s_direction
{
	N,
	S,
	W,
	O,
}	t_dir;

typedef struct s_data_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data_image;

typedef struct t_texture
{
	t_data_image	tex_img[4];
	char			*tex_names[4];
	double			tex_step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	t_data_image	current_tex;
}	t_tex;

typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plan[2];
}	t_player;

/*
	map[] is the player position
*/
typedef struct s_raycasting
{
	double	screen[2];
	double	ray_dir[2];
	int		map[2];
	double	side_dist[2];
	double	delta_dist[2];
	int		step[2];
	double	wall_dist;
	int		hit;
	int		side;
	int		wall_height;
	int		draw_wall[2];
}	t_raycast;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_data_image	data_img;
	t_player		player;
	t_raycast		ray;
	t_tex			tex;
	int				(*map)[24];
}	t_game;

//-------FUNCTIONS-------//

//init.c
void			init(t_game *game);

//textures.c
int				open_textures(t_game *game, t_tex *tex);
void			close_textures(t_game *game);

//utils.c
void			rotate(double src[2], double dest[2], double alpha);
double			to_deg(double alpha);
double			to_rad(double alpha);

//rendering.c
void			rendering(t_game *game);

//raycasting.c
void			raycast(t_game *game, t_player *plyr, t_raycast *ray);

//put_pixel.c
void			put_pixel(t_data_image *data, int x, int y, int color);
unsigned int	read_pixel(t_data_image *data, int x, int y);

//player_movement.c
void			create_new_image(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

//player_rotation.c
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

#endif
