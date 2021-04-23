/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:41:08 by ehande            #+#    #+#             */
/*   Updated: 2021/04/19 21:38:32 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

static int len(char *str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
    i += 1;
	return (i);
}

int add_l_char(char **line, char ch)
{
    int i;
    char *out;
    char *tmp;

    tmp = *line;
    i = len(tmp);
    if(!(out = malloc(sizeof(char) * (i + 1))))
        return (0);
    out[i] = '\0';
    out[--i] = ch;
    while (i--)
        out[i] = tmp[i];
    free(*line);
    *line = out;
    return (1);
}

int add_f_char(char **line, char ch)
{
    int i;
    char *out;
    char *tmp;

    tmp = *line;
    i = len(tmp);
    if(!(out = malloc(sizeof(char) * (i + 1))))
        return (0);
    out[i] = '\0';
    --i;
    while (i--)
        out[i + 1] = tmp[i];
    out[0] = ch;
    free(*line);
    *line = out;
    return (1);
}

int add_char_index(char **line, char ch, int index)
{
    int i;
    int j;
    char *out;
    char *tmp;

    tmp = *line;
    i = len(tmp);
    if(!(out = malloc(sizeof(char) * (i + 1))))
        return (0);
    out[i] = '\0';
    j = -1;
    i = -1;
    while (tmp[++i])
        if (++j == index)
        {
            i--;
            out[j] = ch;
        }
        else
            out[j] = tmp[i];
    if (i == j + 1)
        out[++j] = ch;
    free(*line);
    *line = out;
    return (1);
}
