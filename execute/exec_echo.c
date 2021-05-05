/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:12:04 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/05 15:56:08 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_msh *msh, char **line, int i, int j)
{
	while (line[++i])
	{
		if (i > j)
			write(msh->fd, " ", 1);
		write (msh->fd, line[i], ft_strlen(line[i]));
	}
}

int	exec_echo(t_msh *msh)
{
	if (!ft_strcmp(msh->cmd->arg[1], "-n"))
		print_echo(msh, msh->cmd->arg, 1, 2);
	else
	{
		if (msh->cmd->arg[1])
			print_echo(msh, msh->cmd->arg, 0, 1);
		write (msh->fd, "\n", 1);
	}
	msh->code = 0;
	return (1);
}
