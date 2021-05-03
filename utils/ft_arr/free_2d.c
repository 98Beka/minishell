/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:39:05 by ehande            #+#    #+#             */
/*   Updated: 2021/05/04 02:18:14 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"
#include "../libft/libft.h"

void	free_2d(char ***input)
{
	int	i;
	
	i = 0;
	while ((*input)[i])
		free((*input)[i++]);
	**input = NULL;
}
