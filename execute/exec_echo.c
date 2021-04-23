/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:12:04 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/22 20:15:25 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_msh *msh, char **cmd)
{
	while (*cmd)
	{
		write (msh->fd, *cmd, ft_strlen(*cmd));
		cmd++;
		if (*cmd)
			write(msh->fd, " ", 1);
	}
}

int	exec_echo(t_msh *msh)
{
	msh->cmd->arg++;
	if (!ft_strcmp(*msh->cmd->arg, "-n") && *msh->cmd->arg)
		print_echo(msh, ++msh->cmd->arg);
	else
	{
		if (*msh->cmd->arg)
			print_echo(msh, msh->cmd->arg);
		write (msh->fd, "\n", 1);
	}
	return (1);
}
