/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:57:21 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 15:57:22 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

int	exec_redirect(t_msh *msh, t_cmd *cmnd)
{
	if ((!cmnd->file) && (cmnd->r_redir != 0 || cmnd->dbl_r_redir != 0))
		return (ft_error(msh, "syntax error unexpected token `newline'",
				NULL, 1));
	if (cmnd->r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 1", NULL, 1));
		dup2(msh->fd, STDOUT_FILENO);
	}
	else if (cmnd->dbl_r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 2", NULL, 1));
		dup2(msh->fd, STDOUT_FILENO);
	}
	else if (cmnd->l_redir == 1)
	{
		msh->fd = open(cmnd->file, O_RDONLY);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 3", NULL, 1));
		dup2(msh->fd, STDIN_FILENO);
	}
	return (1);
}
