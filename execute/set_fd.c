/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:29:14 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 15:59:26 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_fd(t_msh *msh)
{
	msh->fd = 1;
	if ((!msh->cmd->file && msh->cmd->r_redir != 0)
		|| (!msh->cmd->file && msh->cmd->dbl_r_redir != 0))
		return (ft_error(msh, "syntax error unexpected token `newline'",
				NULL, 1));
	else if (msh->cmd->r_redir == 1)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL, NULL, 1);
	}
	else if (msh->cmd->dbl_r_redir == 1)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL, NULL, 1);
	}
	return (1);
}
