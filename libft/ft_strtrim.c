/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:47:17 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/04/06 15:47:17 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	isinset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	startword(const char *s1, const char *set, int *i)
{
	while (s1[*i] && isinset(set, s1[*i]) == 1)
		*i += 1;
}

static void	endword(const char *s1, const char *set, int *j)
{
	while (*j > 0 && isinset(set, s1[*j]) == 1)
		*j -= 1;
}

static void	setvar(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	int		lens1;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	lens1 = ft_strlen(s1);
	setvar(&i, &k);
	startword(s1, set, &i);
	if (i == lens1)
		return (ft_strdup(""));
	j = lens1 - 1;
	endword(s1, set, &j);
	str = (char *)malloc(sizeof(char) * (((j + 1) - i) + 1));
	if (!str)
		return (NULL);
	while (k < (j + 1) - i)
	{
		str[k] = s1[i + k];
		k++;
	}
	str[k] = '\0';
	return (str);
}
