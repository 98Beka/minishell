/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:04:55 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 17:24:35 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char	*line;

	line = malloc(sizeof(char) * 1);
	line[0] = '\0';
	add_char_index(&line, 'a', 0);
	add_char_index(&line, 'b', 1);
	return (0);
}
