/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:33:38 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/04 02:34:40 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;
	
	if (!src)
	return (NULL);
	len = 0;
	while (src[len] != '\0')
		len++;
	dup = malloc(len + 1);
	if (dup == 0)
		return (0);
	dup[len] = '\0';
	len = 0;
	while (src[len] != '\0')
	{
		dup[len] = src[len];
		len++;
	}
	return (dup);
}
