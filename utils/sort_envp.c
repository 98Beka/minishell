/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:06:19 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/14 20:02:55 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_envp(char ***env)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = 0;
	while ((*env)[size])
		size++;
	while (++i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp((*env)[j], (*env)[i]) > 0)
			{
				tmp = (*env)[i];
				(*env)[i] = (*env)[j];
				(*env)[j] = tmp;
			}
			j++;
		}
	}
}
