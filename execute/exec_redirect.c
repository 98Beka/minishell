/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:57:21 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 11:15:21 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>

int	exec_redirect(t_msh *msh, t_cmd *cmnd)
{
	if (cmnd->r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_RDWR | O_TRUNC, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, NULL));
		dup2(msh->fd, STDOUT_FILENO);
	}
	else if (cmnd->dbl_r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_RDWR | O_TRUNC | O_APPEND, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, NULL));
		dup2(msh->fd, STDOUT_FILENO);
	}
	else if (cmnd->l_redir == 1)
	{
		msh->fd = open(cmnd->file, O_RDONLY);
		if (msh->fd < 0)
			return (ft_error(msh, NULL));
		dup2(msh->fd, STDIN_FILENO);
	}
	close(msh->fd);
	return (1);
}
