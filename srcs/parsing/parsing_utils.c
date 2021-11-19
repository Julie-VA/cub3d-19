/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:48:33 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/12 11:49:18 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f');
}

int	check_around(char **map, int x, int y, int height)
{
	if (y == 0)
	{
		if (map[y + 1][x] == '1' || is_space(map[y + 1][x]))
			if (map[y][x - 1] == '1' || is_space(map[y][x - 1]))
				if (map[y][x + 1] == '1' || is_space(map[y][x + 1]))
					return (0);
	}
	else if (y == height)
	{
		if (map[y - 1][x] == '1' || is_space(map[y - 1][x]))
			if (map[y][x - 1] == '1' || is_space(map[y][x - 1]))
				if (map[y][x + 1] == '1' || is_space(map[y][x + 1]))
					return (0);
	}
	else
	{
		if (map[y - 1][x] == '1' || is_space(map[y - 1][x]))
			if (map[y + 1][x] == '1' || is_space(map[y + 1][x]))
				if (map[y][x - 1] == '1' || is_space(map[y][x - 1]))
					if (map[y][x + 1] == '1' || is_space(map[y][x + 1]))
						return (0);
	}
	return (1);
}
