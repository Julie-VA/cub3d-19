/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:42:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/16 18:47:50 by rvan-aud         ###   ########.fr       */
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

int	get_multipl(int height, int *maxl)
{
	if (*maxl > 200 || height > 150)
		return (2);
	else if (*maxl > 130 || height > 100)
		return (3);
	else if (*maxl > 90 || height > 60)
		return (4);
	else if (*maxl > 45 || height > 30)
		return (5);
	else if (*maxl > 25 || height > 15)
		return (8);
	else if (*maxl > 20 || height > 10)
		return (15);
	else
		return (25);
}

char **alloc_minimap(char **map, int *maxl, int *multipl)
{
	int	height;
	char **minimap;
	int	i;

	*maxl = get_maxl(map);
	height = get_map_height(map);
	*multipl = get_multipl(height, multipl);
	minimap = (char **)malloc(sizeof(char *) * ((height * *multipl) + 1));
	if (!minimap)
		return (NULL);
	i = 0;
	while (i < height * *multipl)
	{
		minimap[i] = (char *)malloc(sizeof(char) * ((*maxl * *multipl) + 1));
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
	int	multipl;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	minimap = alloc_minimap(file->map, &maxl, &multipl);
	if (!minimap)
		return (NULL);
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (file->map[y][x] == '1')
				minimap[j + (y * multipl)][i + (x * multipl)] = '1';
			else if (file->map[y][x] == ' ')
				minimap[j + (y * multipl)][i + (x * multipl)] = ' ';
			else
				minimap[j + (y * multipl)][i + (x * multipl)] = '0';
			if (i == multipl - 1)
			{
				i = 0;
				x++;
				continue ;
			}
			i++;
		}
		while (x < maxl)
		{
			if (i == multipl)
			{
				i = 0;
				x++;
				continue ;
			}
			minimap[j + (y * multipl)][i + (x * multipl)] = ' ';
			i++;
		}
		minimap[j + (y * multipl)][x * multipl] = '\0';
		if (j == multipl - 1)
		{
			j = 0;;
			y++;
			continue ;
		}
		j++;
	}
	minimap[y * multipl] = NULL;
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
