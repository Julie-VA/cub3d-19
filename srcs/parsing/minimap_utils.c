/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:36:45 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 13:40:48 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_maxl(char **map)
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

char	**alloc_minimap(char **map, int *maxl, int *multipl)
{
	int		height;
	char	**minimap;
	int		i;

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
