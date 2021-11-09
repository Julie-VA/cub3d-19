#include "cub3d.h"

static int	check_only_spaces(char *line)
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

int	check_after_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
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

int	rem_trailing_spaces(char **map_f, char **raw_file, int end)
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
		map_f[i] = (char *)malloc(sizeof(char) * (len + 2));
		if (!map_f[i])
			return (1);
		j = -1;
		while (++j <= len)
			map_f[i][j] = raw_file[i][j];
		map_f[i][j] = '\0';
		i++;
	}
	map_f[i] = NULL;
	return (0);
}

int	get_map(t_map *map)
{
	int	i;
	int	save;

	i = 0;
	while (map->raw_file[i] && (map->raw_file[i][0] != '1' && map->raw_file[i][0] != '0' && check_after_spaces(map->raw_file[i])))
	{
		if (map->raw_file[i][0] == 'N' || map->raw_file[i][0] == 'S')
			if (map->raw_file[i][1] != 'O')
				break ;
		if (map->raw_file[i][0] == 'W')
			if (map->raw_file[i][1] != 'E')
				break ;
		if (map->raw_file[i][0] == 'E')
			if (map->raw_file[i][1] != 'A')
				break ;
		i++;
	}
	save = i;
	while (map->raw_file[i])
	{
		if (check_only_spaces(map->raw_file[i]))
		{
			i--;
			break ;
		}
		i++;
	}
	// printf("i - save + 1=%d\n", i - save + 1);
	map->map_f = (char **)malloc(sizeof(char *) * (i - save + 2));
	if (!map->map_f)
		return (1);
	//j = 0;
//	while (save <= i)
//		map->map_f[j++] = map->raw_file[save++];
//	map->map_f[j] = NULL;
	rem_trailing_spaces(map->map_f, map->raw_file + save, i - save);
	// printf("\n");
	// i = 0;
	// while (map->map_f[i])
	// {
	// 	printf("map_f[%d]=|%s|\n", i, map->map_f[i]);
	// 	i++;
	// }
	return (0);
}
