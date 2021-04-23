/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:33:38 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/23 12:27:13 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int	exec_child(t_msh *msh, char *path)
//{
//	if (msh->cmd->r_redir > 0)
//		dup2(msh->fd, 1);
//	else if (msh->cmd->pipe)
//	{
//		close(msh->pfd[0]);
//		dup2(msh->pfd[1], 1);
//		close(msh->pfd[1]);
//	}
//	if (execve(path, msh->cmd->arg, msh->env) < 0)
//		ft_error(msh, NULL);
//	free(path);
//	exit(0);
//}
