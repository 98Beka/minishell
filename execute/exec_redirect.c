/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:57:21 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 18:10:55 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

int	exec_redirect(t_msh *msh, t_cmd *cmnd)
{
	int	saved_stdout;
	saved_stdout = dup(STDOUT_FILENO); //сохраним старый STDOUT, чтобы можно было передать в другой процесс

	if ((!cmnd->file) && (cmnd->r_redir != 0 || cmnd->dbl_r_redir != 0))
		return (ft_error(msh, "syntax error unexpected token `newline'",
				NULL, 1));
	if (cmnd->r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 1", NULL, 1));
		dup2(msh->fd, STDOUT_FILENO); //подменим его на fd открытого файла
	}
	else if (cmnd->dbl_r_redir == 1)
	{
		msh->fd = open(cmnd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 2", NULL, 1));
		dup2(msh->fd, STDOUT_FILENO); //подменим его на fd открытого файла
	}
	else if (cmnd->l_redir == 1)
	{
		msh->fd = open(cmnd->file, O_RDONLY);
		if (msh->fd < 0)
			return (ft_error(msh, "NULL 3", NULL, 1));
		dup2(msh->fd, STDIN_FILENO);
	}
	//close(msh->fd);
	//dup2(saved_stdout, STDOUT_FILENO); //восстановим старый STDOUT
	//close(saved_stdout);
	return (1);
}
