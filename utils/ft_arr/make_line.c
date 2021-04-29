/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:51:24 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 17:20:16 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

int	make_line(char **line, char ch)
{
	if ((*line) == NULL)
	{
		*line = malloc(sizeof(char));
		*line[0] = '\0';
	}
	if (ch == '\n')
		return (0);
	add_l_char(line, ch);
	return (1);
}
