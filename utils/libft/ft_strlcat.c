/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:48:10 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/08 17:53:42 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	n;

	d = 0;
	n = 0;
	s = 0;
	while (dst[d] != '\0' && d < size)
		d++;
	while (src[n] != '\0' && d + n + 1 < size)
	{
		dst[d + n] = src[n];
		n++;
	}
	if (d != size)
		dst[d + n] = '\0';
	while (src[s] != '\0')
		s++;
	return (d + s);
}
