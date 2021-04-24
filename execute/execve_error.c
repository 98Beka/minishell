/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:40:16 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 15:32:51 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execve_error(t_msh *msh, char *path)
{
	if (!ft_strncmp(path, "./", 2))
		ft_error(msh, "permission denied", NULL);
	else if (ft_strchr(path, '/'))
	{
		msh->dir = opendir(path);
		if (!(msh->dir))
			ft_error(msh, "no such file or directory", NULL);
		else
		{
			ft_error(msh, "is a directory", NULL);
			closedir(msh->dir);
		}
	}
	free(path);
	return (0);
}
