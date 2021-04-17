/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:29:21 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/06 08:50:07 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		sign;
	int		r;

	i = 0;
	res = 0;
	sign = 1;
	r = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' ||
	str[i] == '\r' || str[i] == '\n' || str[i] == ' ')
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		r++;
	}
	if (r >= 19 && sign == 1)
		return (-1);
	else if (r >= 19 && sign == -1)
		return (0);
	return ((sign < 0) ? (sign * res) : (sign * res));
}
