/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:19:33 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 23:53:15 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_envp(char **envp, t_msh *msh)
{
	int	 i;

	i = -1;
	msh->env = new_2d(0);
	while (envp[++i])
		add_l_line(&msh->env, ft_strdup(envp[i]));
	return (1);
}
