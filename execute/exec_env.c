/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:36:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 11:56:28 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->env[i])
	{
		if (ft_strrchr(msh->env[i], '='))
			ft_putendl_fd(msh->env[i], msh->fd);
		i++;
	}
	return (1);
}
