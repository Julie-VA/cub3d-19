/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:14:33 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 18:09:47 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

# define SCREEN_W 1920
# define SCREEN_H 1080
# define EVENT_DEST 17

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_L 123
# define KEY_R 124
# define KEY_ESC 53

typedef struct s_file
{
	char			**raw_file;
	char			**map;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	char			*f_str;
	char			*c_str;
	unsigned int	f_color;
	unsigned int	c_color;
	int				p_pos_x;
	int				p_pos_y;
	char			p_ori;
	char			**minimap;
	int				multipl;
}	t_file;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_icoord
{
	int	x;
	int	y;
}	t_icoord;

typedef struct s_fcoord
{
	float	x;
	float	y;
}	t_fcoord;

typedef struct s_group
{
	t_icoord	xy;
	t_icoord	ij;
}	t_group;

typedef struct s_data
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	t_icoord		size;
	int				line_len;
	int				endian;
}	t_data;

typedef struct s_player
{
	t_fcoord	pos;
	t_fcoord	dir;
	t_fcoord	plane;
}	t_player;

typedef struct s_game
{
	t_player	*p;
	t_file		*file;
}	t_game;

typedef struct s_tex
{
	t_data			n;
	t_data			s;
	t_data			e;
	t_data			w;
	unsigned int	f_color;
	unsigned int	c_color;
	unsigned int	bg_c;
}	t_tex;

typedef struct s_mlx
{
	t_vars		vars;
	t_tex		tex;
	t_data		buff;
	t_game		*game;
	t_file		*file;
}	t_mlx;

/*
** parsing/
*/

// get_map_checks
int				check_only_spaces(char *line);
int				check_after_space(char *line);
int				check_if_player_on_border(t_file *file, int *i);
int				check_last_line(char **raw_file);

// get_map
int				get_map(t_file *map, int i);

// get_textures_pos
unsigned int	get_bg_color(char *color);
int				get_textures(t_file *map);
int				get_pos(t_file *map);

// minimap_utils
int				get_multipl(int height, int *maxl);
char			**alloc_minimap(char **map, int *maxl, int *multipl);

// minimap
char			**set_minimap(t_file *file);
void			draw_player(int multipl, t_data buff, t_fcoord pos);
t_icoord		print_minimap(char **minimap, t_data buff, unsigned int bg_c);

// modgnl_utils
int				get_next_line(int fd, char **line);
int				ft_modstrlen(const char *s, int mod);
char			*ft_modstrjoin(char const *s1, char const *s2);

// modgnl
int				get_next_line(int fd, char **line);

// parsing_utils
int				get_map_height(char **map);
int				check_around(char **map, int x, int y, int height);

// parsing
int				parsing(char *argv, t_file *map);

// read_file
int				check_cub(char *str);
char			**read_file(char *argv);

/*
** raycast/
*/

// draw
void			draw(int lineHeight, t_tex tex_s, unsigned int *buff,
					unsigned int *tex);
int				get_tex_x(int side, t_fcoord ray_dir,
					float perpWallDist, const t_player *p);
t_data			get_side_tex(int side, t_fcoord ray_dir, t_tex tex);

// raycast
int				raycast(t_mlx *mlx);

/*
** srcs/
*/

// free
int				free_file(t_file *file);
int				free_all_but_mini(t_file *file);
int				free_all(t_file *file);

// init
void			*game_init(t_file *file);
int				hook_init(t_vars vars, t_tex tex, t_file *file, t_data buff);
int				tex_init(t_file *file, void *mlx, t_tex *tex);
t_player		*player_init(t_file *file);

// key_rotations
void			key_r(t_game *g, float old_dirx, float old_planex);
void			key_l(t_game *g, float old_dirx, float old_planex);
int				key_press(int keycode, t_mlx *mlx_all);

#endif