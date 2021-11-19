/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:50:28 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/19 12:42:48 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_bg_color(char *color, int *check)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(color, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		write(2, "Error\nInvalid texture color\n", 28);
		*check = 1;
		return (0);
	}
	return ((r << 16) | (g << 8) | b);
}

static char	*get_each_texture(t_file *file, char *prefix, int offset)
{
	int	i;
	int	j;

	i = 0;
	while (file->raw_file[i])
	{
		j = 0;
		while (is_space(file->raw_file[i][j]))
			j++;
		if (!ft_strncmp_space(prefix, file->raw_file[i], offset))
		{
			while (is_space(file->raw_file[i][offset + j]))
				offset++;
			return (file->raw_file[i] + (offset + j));
		}
		i++;
	}
	return (NULL);
}

int	get_textures(t_file *file)
{
	int	check;

	check = 0;
	file->n_texture = get_each_texture(file, "NO", 2);
	file->s_texture = get_each_texture(file, "SO", 2);
	file->w_texture = get_each_texture(file, "WE", 2);
	file->e_texture = get_each_texture(file, "EA", 2);
	file->f_str = get_each_texture(file, "F", 1);
	file->c_str = get_each_texture(file, "C", 1);
	if (!file->n_texture || !file->s_texture || !file->w_texture
		|| !file->e_texture || !file->f_str || !file->c_str)
	{
		write(2, "Error\nMissing or invalid texture path(s)\n", 41);
		return (1);
	}
	file->f_color = get_bg_color(file->f_str, &check);
	file->c_color = get_bg_color(file->c_str, &check);
	if (check == 1)
		return (1);
	return (0);
}

static int	check_pos(t_file *file, int x, int y, char ori)
{
	if (file->map[y][x] == ori)
	{
		file->p_pos_x = x;
		file->p_pos_y = y;
		file->p_ori = ori;
		return (1);
	}
	return (0);
}

int	get_pos(t_file *file)
{
	int	x;
	int	y;

	y = 1;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (check_pos(file, x, y, 'N') || check_pos(file, x, y, 'S')
				|| check_pos(file, x, y, 'W') || check_pos(file, x, y, 'E'))
				return (0);
			x++;
		}
		y++;
	}
	write(2, "Error\nNo player position or invalid orientation\n", 48);
	return (1);
}
