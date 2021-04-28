/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:08:03 by ehande            #+#    #+#             */
/*   Updated: 2021/04/28 11:08:19 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rmdr(char *sbf, int i, int j)
{
	char	*buff;

	if (!sbf)
		return (0);
	while (sbf[i] && sbf[i] != '\n')
		i++;
	if (!sbf[i])
	{
		free(sbf);
		return (0);
	}
	while (sbf[j])
		j++;
	if (!(buff = malloc(sizeof(char) * ((j - i) + 1))))
		return (0);
	j = 0;
	i++;
	while (sbf[i])
		buff[j++] = sbf[i++];
	buff[j] = '\0';
	free(sbf);
	return (buff);
}