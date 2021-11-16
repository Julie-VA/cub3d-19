/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:42:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/16 16:58:33 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_maxl(char **map)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	y = 0;
	len = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > len)
			len = x;
		y++;
	}
	return (len);
}

char **alloc_minimap(char **map, int *maxl)
{
	int	height;
	char **minimap;
	int	i;

	*maxl = get_maxl(map);
	height = get_map_height(map);
	minimap = (char **)malloc(sizeof(char *) * ((height * 5) + 1));
	if (!minimap)
		return (NULL);
	i = 0;
	while (i < height * 5)
	{
		minimap[i] = (char *)malloc(sizeof(char) * ((*maxl * 5) + 1));
		if (!minimap)
			return (NULL);
		i++;
	}
	minimap[i] = NULL;
	return (minimap);
}

char	**set_minimap(t_file *file)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	maxl;
	char **minimap;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	minimap = alloc_minimap(file->map, &maxl);
	if (!minimap)
		return (NULL);
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (file->map[y][x] == '1')
				minimap[j + (y * 5)][i + (x * 5)] = '1';
			else if (file->map[y][x] == ' ')
				minimap[j + (y * 5)][i + (x * 5)] = ' ';
			else
				minimap[j + (y * 5)][i + (x * 5)] = '0';
			if (i == 4)
			{
				i = 0;
				x++;
				continue ;
			}
			i++;
		}
		while (x < maxl)
		{
			if (i == 5)
			{
				i = 0;
				x++;
				continue ;
			}
			minimap[j + (y * 5)][i + (x * 5)] = ' ';
			i++;
		}
		minimap[j + (y * 5)][x * 5] = '\0';
		if (j == 4)
		{
			j = 0;;
			y++;
			continue ;
		}
		j++;
	}
	minimap[y * 5] = NULL;
	return (minimap);
}

t_icoord	print_minimap(t_file *file, t_data *buff, unsigned int bg_c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (file->minimap[y])
	{
		x = 0;
		while (file->minimap[y][x])
		{
			if (file->minimap[y][x] == '1')
				set_px(buff, (t_icoord){x, y}, 0);
			else if (file->minimap[y][x] == '0')
				set_px(buff, (t_icoord){x, y}, bg_c);
			x++;
		}
		y++;
	}
	return ((t_icoord){x, y});
}
