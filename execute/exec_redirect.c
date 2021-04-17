/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:15:31 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/14 20:00:46 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_redirect(t_msh *msh)
{
	pid_t	pid;
	
	pid = fork();
	dup2(msh->pipefd[1], 1);
	if (pid == 0)
	{
		write(msh->pipefd[1], msh->cmd.file, BUFF_SIZE);
	}
	else
	{
		
	}
	close(msh->pipefd[1]);
	return (1);
}
