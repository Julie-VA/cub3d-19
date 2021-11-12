/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:50:08 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/12 14:48:01 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cub(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i--] == 'b')
		if (str[i--] == 'u')
			if (str[i--] == 'c')
				if (str[i] == '.')
					return (1);
	write(2, "Wrong map extension\n", 20);
	return (0);
}

static int	count_lines(char *argv, char **line)
{
	int	fd;
	int	ret;
	int	i;

	i = 0;
	ret = 1;
	fd = open(argv, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, line);
		if (ret == -1)
			return (-1);
		free(*line);
		i++;
	}
	close(fd);
	return (i);
}

char	**read_file(char *argv)
{
	char	*line;
	char	**raw_file;
	int		ret;
	int		i;
	int		fd;

	i = count_lines(argv, &line);
	if (i == -1)
		return (NULL);
	raw_file = (char **)malloc(sizeof(char *) * (i + 1));
	if (!raw_file)
		return (NULL);
	ret = 0;
	ret = 1;
	i = 0;
	fd = open(argv, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &raw_file[i++]);
		if (ret == -1)
		{
			write(2, "Error opening the map\n", 22);
			return (NULL);
		}
	}
	raw_file[i] = NULL;
	close(fd);
	return (raw_file);
}
