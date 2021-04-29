/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 04:15:52 by ehande            #+#    #+#             */
/*   Updated: 2021/04/29 16:02:22 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

int dbl_len(char **input)
{
    int i;

    i = 0;
    if (!input || !*input)
        return (0);
    while (input[i])
        i++;
    return (i);
}
