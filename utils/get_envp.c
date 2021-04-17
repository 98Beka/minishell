/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:19:33 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/09 15:19:51 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_envp(char **envp, t_msh *msh)
{
	int	 i;

	i = 0;
	while (envp[i])
		i++;
	msh->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!msh->env)
		return (0);
	envp[i] = NULL;
	while (envp[--i])
		msh->env[i] = ft_strdup(envp[i]);
	return (1);
}
