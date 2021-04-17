/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:50:54 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/06 10:06:43 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < len && s1[i] == s2[i])
		i++;
	if (i == len)
		return (0);
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
