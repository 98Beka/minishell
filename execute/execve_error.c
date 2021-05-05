/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:40:16 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/05 17:21:08 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

void	execve_error_dop(t_msh *msh, char *path)
{
	msh->dir = opendir(path);
	if (!(msh->dir))
		ft_error(msh, "no such file or directory", NULL, 1);
	else
		ft_error(msh, "is a directory", NULL, 1);
	closedir(msh->dir);
}

int	execve_error(t_msh *msh, char *path, t_cmd *cmd)
{
	msh->dir = NULL;
	if (!ft_strncmp(path, ".\0", 2))
		ft_error(msh, "filename argument required", NULL, 1);
	else if (!ft_strncmp(path, "./\0", 3))
		ft_error(msh, "is a directory", NULL, 1);
	else if (!ft_strncmp(path, "./", 2))
	{
		free(path);
		return (ft_error(msh, "permission denied", NULL, 126) + 126);
	}
	else if (ft_strchr(path, '/'))
		execve_error_dop(msh, path);
	else
	{
		free(path);
		return (ft_error(msh, "command not found", cmd, 127) + 127);
	}
	free(path);
	return (1);
}
