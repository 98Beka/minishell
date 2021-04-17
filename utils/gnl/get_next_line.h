/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 10:01:05 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/04 18:32:04 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *str, int ch);
int					ft_strlen(char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnew(size_t size);

#endif
