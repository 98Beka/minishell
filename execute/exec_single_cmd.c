/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:42:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/11 21:11:33 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

static char	*in_env(t_msh *msh, char *key)
{
	int	i;
	int	len;

	i = -1;
	while (msh->env[++i])
	{
		len = ft_strlen(key);
		if (((ft_strnstr(msh->env[i], key, len))
				&& (msh->env[i][len] == '='))
			|| ((ft_strnstr(msh->env[++i], key, len))
			&& (msh->env[i][len]) == '\0'))
			return (msh->env[i]);
	}
	return (NULL);
}

int	exec_single_cmd(t_msh *msh)
{
	if (!execute(msh, msh->cmd))
	{
		if (!in_env(msh, "PATH"))
			return (ft_error(msh, "No such file or directory", NULL, 1));
		return (exec_bin(msh));
	}
	return (1);
}
