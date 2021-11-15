/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:51:32 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/15 15:52:45 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rem_trailing_spaces(char **map, char **raw_file, int end)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i <= end)
	{
		len = ft_strlen(raw_file[i]);
		while (raw_file[i][--len] == ' ')
			;
		map[i] = (char *)malloc(sizeof(char) * (len + 2));
		if (!map[i])
			return (1);
		j = -1;
		while (++j <= len)
			map[i][j] = raw_file[i][j];
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (0);
}

int	get_map(t_file *file, int i)
{
	int	save;
	int	o;

	while (file->raw_file[i] && (file->raw_file[i][0] != '1'
		&& file->raw_file[i][0] != '0' && check_after_space(file->raw_file[i])))
	{
		if (check_if_player_on_border(file, &i))
			break ;
	}
	o = check_last_line(file->raw_file);
	save = i;
	while (file->raw_file[i])
	{
		if (check_only_spaces(file->raw_file[i]))
		{
			i--;
			break ;
		}
		i++;
	}
	file->map = (char **)malloc(sizeof(char *) * (i - save + 2));
	if (!file->map)
		return (1);
	rem_trailing_spaces(file->map, file->raw_file + save, i - save - o);
	return (0);
}
