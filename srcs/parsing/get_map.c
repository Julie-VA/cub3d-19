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

int	rem_trailing_spaces(char **map, char **raw_file, int end)
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

int	get_map(t_file *file)
{
	int	i;
	int	save;

	i = 0;
	while (file->raw_file[i] && (file->raw_file[i][0] != '1' && file->raw_file[i][0] != '0' && check_after_spaces(file->raw_file[i])))
	{
		if (file->raw_file[i][0] == 'N' || file->raw_file[i][0] == 'S')
			if (file->raw_file[i][1] != 'O')
				break ;
		if (file->raw_file[i][0] == 'W')
			if (file->raw_file[i][1] != 'E')
				break ;
		if (file->raw_file[i][0] == 'E')
			if (file->raw_file[i][1] != 'A')
				break ;
		i++;
	}
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
	// printf("i - save + 1=%d\n", i - save + 1);
	file->map = (char **)malloc(sizeof(char *) * (i - save + 2));
	if (!file->map)
		return (1);
	//j = 0;
//	while (save <= i)
//		file->map[j++] = file->raw_file[save++];
//	file->map[j] = NULL;
	rem_trailing_spaces(file->map, file->raw_file + save, i - save);
	// printf("\n");
	// i = 0;
	// while (file->map[i])
	// {
	// 	printf("map[%d]=|%s|\n", i, file->map[i]);
	// 	i++;
	// }
	return (0);
}
