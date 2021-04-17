/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:52:38 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/06 15:22:36 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		num_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

int		ch_count(int n)
{
	long int	num;
	int			i;

	num = (long int)n;
	i = 0;
	if (n < 0)
		num = -num;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*buf;
	int			i;
	long int	n_mod;

	n_mod = (long int)n;
	n_mod = (num_sign(n)) ? (-n_mod) : (n_mod);
	i = (n_mod != 0) ? (ch_count(n) + num_sign(n)) : 1;
	if (!(buf = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	buf[i] = '\0';
	if (n_mod == 0)
	{
		buf[0] = '0';
		return (buf);
	}
	i--;
	while (i >= 0)
	{
		buf[i] = (n_mod % 10) + '0';
		i--;
		n_mod = n_mod / 10;
	}
	if (num_sign(n))
		buf[0] = '-';
	return (buf);
}
