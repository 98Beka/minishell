/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:54:30 by hveiled           #+#    #+#             */
/*   Updated: 2021/03/18 16:30:49 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	size;
	char			*start;
	char			*end;
	char			*str;

	i = 0;
	if (!s1)
		return (NULL);
	while (check_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	i = ft_strlen((char *)s1) - 1;
	while (i > 0 && check_set(s1[i], set))
		i--;
	end = (char *)&s1[i];
	size = (end - start) + 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, start, size + 1);
	return (str);
}
