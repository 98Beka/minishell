/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:12:04 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/04 10:28:46 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_msh *msh, char **line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if (i > 1)
			write(msh->fd, " ", 1);
		write (msh->fd, line[i], ft_strlen(line[i]));
	}
}

int	exec_echo(t_msh *msh)
{
	if (!ft_strcmp(*msh->cmd->arg, "-n") && *msh->cmd->arg)
		print_echo(msh, msh->cmd->arg);
	else
	{
		if (*msh->cmd->arg)
			print_echo(msh, msh->cmd->arg);
		write (msh->fd, "\n", 1);
	}
	msh->code = 0;
	return (1);
}
