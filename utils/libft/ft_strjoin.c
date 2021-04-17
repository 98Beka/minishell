/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:33:00 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/04 14:02:22 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*s3;
	size_t			l1;
	size_t			l2;
	size_t			i;
	size_t			j;

	i = 0;
	j = i;
	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen((char *)s1);
	l2 = ft_strlen((char *)s2);
	s3 = (unsigned char *)malloc(((l1 + l2) * sizeof(char)) + 1);
	if (!s3)
		return (0);
	while (i < l1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < l2)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return ((char *)s3);
}
