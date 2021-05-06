/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:00:13 by ehande            #+#    #+#             */
/*   Updated: 2021/05/06 14:50:19 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

static int	len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	i += 1;
	return (i);
}

int	add_f_line(char ***input, char *line)
{
	char	**out;
	int		i;

	i = len(*input);
	out = (char **)malloc(sizeof(char *) * (i + 1));
	if (!out)
		return (0);
	out[i] = NULL;
	while (--i)
		out[i] = (*input)[i - 1];
	out[0] = line;
	free(*input);
	*input = out;
	return (1);
}

int	add_l_line(char ***input, char *line)
{
	char	**out;
	int		i;

	i = len(*input);
	out = (char **)malloc(sizeof(char *) * (i + 1));
	if (!out)
		return (0);
	out[i] = NULL;
	out[--i] = line;
	while (i--)
		out[i] = (*input)[i];
	free(*input);
	*input = out;
	return (1);
}

static void	add_l_init(int *i, int *j, char ***out, char ***line)
{
	*i = len(*line);
	(*out) = (char **)malloc(sizeof(char *) * ((*i) + 1));
	(*out)[*i] = NULL;
	*j = -1;
	*i = -1;
}

int	add_l_index(char ***input, char *line, int index)
{
	int		i;
	int		j;
	char	**out;
	char	**tmp;

	tmp = *input;
	add_l_init(&i, &j, &out, input);
	if (!out)
		return (0);
	while (tmp[++i])
		if (++j == index)
		{
			i -= 1;
			out[j] = line;
		}
		else
			out[j] = tmp[i];
	if (i == j + 1)
		out[++j] = line;
	free(*input);
	*input = out;
	return (1);
}
