/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:26:33 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/03 11:29:10 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		k = 0;
		while (big[i] == little[k] && i < len && big[i] != '\0'
		&& little[k] != '\0')
		{
			i++;
			k++;
		}
		if (little[k] == '\0' && i - k < len)
			return ((char *)big + (i - k));
		i = i - k;
		i++;
	}
	return (0);
}
