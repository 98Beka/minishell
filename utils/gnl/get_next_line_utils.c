/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 09:59:04 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/14 12:13:41 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_strchr(const char *str, int ch)
// {
// 	if (str == NULL)
// 		return (NULL);
// 	while (*str != ch)
// 	{
// 		if (*str == '\0')
// 			return (NULL);
// 		str++;
// 	}
// 	return ((char *)str);
// }

// int		ft_strlen(char *str)
// {
// 	int	num;

// 	num = 0;
// 	while (str[num] != '\0')
// 		num++;
// 	return (num);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	unsigned char	*s3;
// 	size_t			l1;
// 	size_t			l2;
// 	size_t			i;
// 	size_t			j;

// 	i = 0;
// 	j = i;
// 	if (!s1 || !s2)
// 		return (0);
// 	l1 = ft_strlen((char *)s1);
// 	l2 = ft_strlen((char *)s2);
// 	s3 = (unsigned char *)malloc(((l1 + l2) * sizeof(char)) + 1);
// 	if (!s3)
// 		return (0);
// 	while (i < l1)
// 	{
// 		s3[i] = s1[i];
// 		i++;
// 	}
// 	while (j < l2)
// 		s3[i++] = s2[j++];
// 	s3[i] = '\0';
// 	// free((char *)s1);
// 	return ((char *)s3);
// }

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}
