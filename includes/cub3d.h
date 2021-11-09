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

typedef struct s_map
{
	char	**raw_file;
	char	**map_f;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*f_color;
	char	*c_color;
	int		p_pos_x;
	int		p_pos_y;
	char	p_ori;
}	t_map;

typedef struct s_icoord
{
	int	x;
	int	y;
}			t_icoord;

typedef struct s_fcoord
{
	float	x;
	float	y;
}			t_fcoord;

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bpp;
	t_icoord	size;
	int			line_len;
	int			endian;
}				t_data;



int		get_next_line(int fd, char **line);
int		ft_modstrlen(const char *s, int mod);
char	*ft_modstrjoin(char const *s1, char const *s2);

char	**read_file(char *argv);
int		check_cub(char *str);
int		raycast(char **worldmap, t_data *img);

int		free_all(t_map *map);

int		parsing(char *argv, t_map *map);

int		get_textures(t_map *map);
int		get_pos(t_map *map);

int		get_map(t_map *map);

#endif