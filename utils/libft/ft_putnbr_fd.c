/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:08:41 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/07 11:32:42 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int		counter(int n)
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

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_mod;
	char		num[20];
	int			i;

	i = 0;
	n_mod = (long int)n;
	n_mod = (n < 0) ? -n_mod : n_mod;
	i = counter(n);
	i = (n < 0) ? (i + 1) : i;
	if (n == 0)
		i = 1;
	num[i] = '\0';
	i--;
	while (i >= 0)
	{
		num[i] = n_mod % 10 + '0';
		n_mod = n_mod / 10;
		i--;
	}
	i++;
	if (n < 0)
		num[0] = '-';
	ft_putstr_fd(num, fd);
}
