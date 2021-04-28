/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:30:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 11:09:08 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoingnl(char const *s1, char const *s2)
{
	char	*p;
	size_t	t1;
	size_t	t2;
	size_t	t3;

	t1 = 0;
	t2 = 0;
	if (s2 == NULL)
		return ((char *)s1);
	if (s1)
		while (s1[t1] != '\0')
			t1++;
	while (s2[t2] != '\0')
		t2++;
	if (!(p = (char *)malloc(sizeof(*s1) * (t1 + t2 + 1))))
		return (NULL);
	t3 = t1;
	p[t1 + t2] = '\0';
	while (t1--)
		p[t1] = s1[t1];
	while (t2--)
		p[t3 + t2] = s2[t2];
	free((char *)s1);
	return (p);
}

static int		ft_strchrgnl(const char *s, int c)
{
	char *str;

	if (s == NULL)
		return (0);
	str = (char *)s;
	while (c != *str && *str != '\0')
		str++;
	if (*str != c)
		return (0);
	return (1);
}

static int		outbf(char **line, char *str)
{
	int		i;
	char	*bf;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(bf = malloc(sizeof(char) * (i + 1))))
		return (0);
	bf[i] = '\0';
	while (i--)
		bf[i] = str[i];
	*line = bf;
	return (1);
}

static int		rd_file(int ri, int fd, char *buff, char **sbf)
{
	if ((ri = read(fd, buff, BUFFER_SIZE)) == -1)
	{
		free(buff);
		return (-1);
	}
	buff[ri] = '\0';
	*sbf = ft_strjoingnl(*sbf, buff);
	return (ri);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*sbf[200];
	int				ri;

	ri = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_strchrgnl(sbf[fd], '\n') && ri != 0)
		if ((ri = rd_file(ri, fd, buff, &sbf[fd])) == -1)
			return (-1);
	free(buff);
	if (!outbf(line, sbf[fd]))
		return (-1);
	sbf[fd] = rmdr(sbf[fd], 0, 0);
	if (ri == 0)
		return (0);
	return (1);
}