/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:01:25 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/04/02 11:01:28 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*scpy;

	scpy = (char *)s;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (scpy[i] == (char)c)
			return (scpy + i);
		i--;
	}
	return ((void *)0);
}
