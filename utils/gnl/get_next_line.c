/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:30:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/02 17:38:08 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remain(char *remain)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!remain)
		return (0);
	while (remain[i] != '\0' && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * ((ft_strlen(remain) - i) + 1))))
		return (0);
	i++;
	while (remain[i] != '\0')
		str[j++] = remain[i++];
	str[j] = '\0';
	free(remain);
	return (str);
}

char	*get_line(char *str)
{
	int		i;
	char	*buf;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!(buf = malloc(sizeof(char) * (i + 1))))
		return (0);
	buf[i] = '\0';
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		buf[i] = str[i];
		i++;
	}
	return (buf);
}

int		get_next_line(int fd, char **line)
{
	static char *remain;
	char		*buffer;
	int			bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	bytes = 1;
	if (!remain)
		remain = ft_strnew(1);
	while (bytes != 0 && !ft_strchr(remain, '\n'))
	{
		if ((bytes = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[bytes] = '\0';
		remain = ft_strjoin(remain, buffer);
	}
	free(buffer);
	*line = get_line(remain);
	remain = get_remain(remain);
	return ((bytes == 0) ? 0 : 1);
}
