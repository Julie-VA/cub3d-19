/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:57:00 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/15 15:52:02 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_after_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		if (line[i] == 'N' || line[i] == 'S')
			if (line[i + 1] == 'O')
				return (1);
		if (line[i] == 'W')
			if (line[i + 1] == 'E')
				return (1);
		if (line[i] == 'E')
			if (line[i + 1] == 'A')
				return (1);
		return (0);
	}
	return (1);
}

int	check_if_player_on_border(t_file *file, int *i)
{
	if (file->raw_file[*i][0] == 'N' || file->raw_file[*i][0] == 'S')
		if (file->raw_file[*i][1] != 'O')
			return (1);
	if (file->raw_file[*i][0] == 'W')
		if (file->raw_file[*i][1] != 'E')
			return (1);
	if (file->raw_file[*i][0] == 'E')
		if (file->raw_file[*i][1] != 'A')
			return (1);
	(*i)++;
	return (0);
}

int	check_last_line(char **raw_file)
{
	int	i;
	int	j;

	i = 0;
	while (raw_file[i + 1])
		i++;
	j = 0;
	while (raw_file[i][j])
	{
		if (raw_file[i][j] == '1' || raw_file[i][j] == '0'
			|| raw_file[i][j] == 'N' || raw_file[i][j] == 'S'
			|| raw_file[i][j] == 'W' || raw_file[i][j] == 'E')
			return (1);
	}
	return (0);
}
