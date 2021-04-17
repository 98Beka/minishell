/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 08:53:41 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/11 14:31:06 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lines(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	clear(char **str, int i)
{
	i--;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static void	word(char const *s, char c, int *start, int *end)
{
	*start = *start + *end;
	*end = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + *end] != c && s[*start + *end] != '\0')
		(*end)++;
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		start;
	int		end;

	if (s == NULL)
		return (NULL);
	if (!(str = (char **)ft_calloc(sizeof(char *), (lines(s, c) + 1))))
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i < lines(s, c))
	{
		word(s, c, &start, &end);
		if (!(str[i] = (char *)malloc(sizeof(char) * (end + 1))))
		{
			clear(str, i);
			return (NULL);
		}
		ft_strlcpy(str[i], &s[start], end + 1);
		i++;
	}
	return (str);
}
