/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:46:41 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/10 09:44:31 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	amount;
	int		i;

	i = 0;
	amount = count * size;
	mem = malloc(amount);
	if (!mem)
		return (0);
	while (amount > 0)
	{
		mem[i++] = 0;
		amount--;
	}
	return (mem);
}
