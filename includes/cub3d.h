#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

#define SCREEN_W 1920
#define SCREEN_H 1080
#define EVENT_DEST 1

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
}	t_file;

typedef struct s_icoord
{
	int	x;
	int	y;
}			t_icoord;

typedef struct s_fcoord
{
	double	x;
	double	y;
}			t_fcoord;

typedef struct s_data {
	void		*img;
	void		*bg;
	char		*addr;
	int			bpp;
	t_icoord	size;
	t_icoord	size_bg;
	int			line_len;
	int			endian;
}				t_data;

typedef struct s_player
{
	t_fcoord	pos;
	t_fcoord	dir;
	t_fcoord	plane;
}				t_player;

typedef struct s_game
{
	t_player	player;
	char**		map;
}		t_game;


typedef struct s_mlx
{
	void*		win;
	void*		mlx;
	t_data		*purple;
	t_data		*blue;
	t_data		*grey;
	t_data		*brick;
	t_data		*buff;
	t_data		*neuve;
	t_file		*file;
}				t_mlx;

t_fcoord ppos;
t_fcoord pdir;
t_fcoord pplane;

void	set_px(t_data *data, t_icoord coord, unsigned int color);

int		get_next_line(int fd, char **line);
int		ft_modstrlen(const char *s, int mod);
char	*ft_modstrjoin(char const *s1, char const *s2);

char	**read_file(char *argv);
int		check_cub(char *str);
int		raycast(t_mlx *mlx);

int		free_file(t_file *file);
int		free_all(t_file *file);

int		parsing(char *argv, t_file *map);

int		get_map_height(char **map);
int		check_around(char **map, int x, int y, int height);

int		get_textures(t_file *map);
int		get_pos(t_file *map);

int		get_map(t_file *map, int i);

int		check_only_spaces(char *line);
int		check_after_space(char *line);
int		check_if_player_on_border(t_file *file, int *i);
int		check_last_line(char **raw_file);

int		key_pressnew(int keycode, t_game *game);
#endif