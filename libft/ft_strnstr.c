/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 12:30:55 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/04/02 12:31:01 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mstrcmp(char *str, char *to_find, int j)
{
	int	i;

	i = 0;
	while (str[j] == to_find[i] && str[j] != '\0' && to_find[i] != '\0')
	{
		i++;
		j++;
	}
	if (str[j] != to_find[i] && to_find[i] != '\0')
		return (0);
	else
		return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	char	*haystackcpy;
	char	*needlecpy;

	j = 0;
	haystackcpy = (char *)haystack;
	needlecpy = (char *)needle;
	if (needlecpy[0] == '\0')
		return (haystackcpy);
	while (j < len && haystackcpy[j] != '\0')
	{
		if (haystackcpy[j] == needlecpy[0])
		{
			if (ft_mstrcmp(haystackcpy, needlecpy, j) == 1)
			{
				if (len < j + (ft_strlen(needlecpy)))
					return ((void *)0);
				return (haystackcpy + j);
			}
		}
		j++;
	}
	return ((void *)0);
}
