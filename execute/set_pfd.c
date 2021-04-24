/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:02:25 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 13:03:23 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_fd(t_msh *msh, int i, int cmd)
{
	if (i == 0)
	{
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, NULL);
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, NULL);
	}
	else if (i == cmd - 1)
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, NULL);
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, NULL);
	}
	else
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, NULL);
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, NULL);
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, NULL);
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, NULL);
	}
}

void	set_pfd(t_msh *msh, int i, int cmd)
{
	if (i == 0)
	{
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, NULL);
	}
	else if (i == cmd - 1)
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, NULL);
	}
	else
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, NULL);
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, NULL);
	}
	close_fd(msh, i, cmd);
}
