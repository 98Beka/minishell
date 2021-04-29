/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 12:51:28 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 17:22:20 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

char	**new_2d(int i)
{
	char	**out;

	if (i < 1)
		i = 1;
	out = (char **)malloc(sizeof(char *) * i);
	if (!out)
		return (NULL);
	while (i--)
		out[i] = NULL;
	return (out);
}
