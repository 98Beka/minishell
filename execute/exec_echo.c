/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:12:04 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 13:30:07 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(char **cmd)
{
	while (*cmd)
	{
		write (1, *cmd, ft_strlen(*cmd));
		cmd++;
		if (*cmd)
			write(1, " ", 1);
	}
}

int	exec_echo(t_msh *msh)
{
	msh->cmd->arg++;
	if (!ft_strcmp(*msh->cmd->arg, "-n") && *msh->cmd->arg)
		print_echo(++msh->cmd->arg);
	else
	{
		if (*msh->cmd->arg)
			print_echo(msh->cmd->arg);
		write (1, "\n", 1);
	}
	return (1);
}
