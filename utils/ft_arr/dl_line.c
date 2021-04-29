/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:13:25 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 17:14:40 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

static int	len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	i -= 1;
	if (i < 0)
		i = 0;
	return (i);
}

int	dl_f_line(char ***input)
{
	char	**out;
	int		i;

	i = len(*input);
	out = (char **)malloc(sizeof(char *) * (i + 1));
	if (!out)
		return (0);
	out[i] = NULL;
	while (i--)
		out[i] = (*input)[i + 1];
	free((*input)[0]);
	free(*input);
	*input = out;
	return (1);
}

int	dl_l_line(char ***input)
{
	char	**out;
	int		i;

	i = len(*input);
	out = (char **)malloc(sizeof(char *) * (i + 1));
	if (!out)
		return (0);
	out[i] = NULL;
	free((*input)[i]);
	while (i--)
		out[i] = (*input)[i];
	free(*input);
	*input = out;
	return (1);
}
