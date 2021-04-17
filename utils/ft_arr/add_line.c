/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:00:13 by ehande            #+#    #+#             */
/*   Updated: 2021/04/16 01:28:23 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

static int len(char **str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
    i += 1;
	return (i);
}

int add_f_line(char ***input, char *line)
{
    char    **out;
    int     i;
    
    i = len(*input);
    if(!(out = (char**)malloc(sizeof(char*) * (i + 1))))
        return(0);
    out[i] = NULL;
    while (--i)
        out[i] = (*input)[i - 1];
    out[0] = line;
    free(*input);
    *input = out;
    return(1);
}

int add_l_line(char ***input, char *line)
{
    char    **out;
    int     i;
    
    i = len(*input);
    if(!(out = (char**)malloc(sizeof(char*) * (i + 1))))
        return(0);
    out[i] = NULL;
    out[--i] = line;
    while (i--)
        out[i] = (*input)[i];
    free(*input);
    *input = out;
    return(1);
}