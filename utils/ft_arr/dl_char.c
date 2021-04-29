/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:33:12 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 17:10:49 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

static int	len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	del_from_index(char **line, int index)
{
	int		i;
	char	*out;
	char	*tmp;

	tmp = *line;
	i = index;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (0);
	out[i] = '\0';
	while (i--)
		out[i] = tmp[i];
	free(*line);
	*line = out;
	return (1);
}

int	del_to_index(char **line, int index)
{
	int		i;
	char	*out;
	char	*tmp;

	tmp = *line;
	i = len(*line) - index;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (0);
	out[i] = '\0';
	while (i--)
		out[i] = tmp[i + index];
	free(*line);
	*line = out;
	return (1);
}

int	del_at_index(char **line, int index)
{
	int		i;
	char	*out;
	char	*tmp;

	tmp = *line;
	i = len(tmp) - 1;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (0);
	out[i] = '\0';
	while (i--)
		if (i < index)
			out[i] = tmp[i];
	else
		out[i] = tmp[i + 1];
	free(*line);
	*line = out;
	return (1);
}
