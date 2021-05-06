/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:04:55 by ehande            #+#    #+#             */
/*   Updated: 2021/05/06 14:51:14 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void print(char **d_arr)
{
	int i;

	i = -1;
	while (d_arr[++i])
		printf("%s\n", d_arr[i]);
	printf("%s\n", d_arr[i]);
}

int	main(void)
{
	char	**d_arr;

	d_arr = new_2d(2);
	d_arr[0] = strdup("hi");
	add_l_index(&d_arr, strdup("world"), dbl_len(d_arr) );
	add_l_index(&d_arr, strdup("!"), dbl_len(d_arr));
	print(d_arr);
	return (0);
}
