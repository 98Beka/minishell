/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:28:56 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 13:30:37 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipe(t_msh *msh)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(msh->pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return (0);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		printf("\nCould not fork");
		return (0);
	}
	if (pid1 == 0)
	{
		// Child 1 executing..
		// It only needs to write at the write end
		close(msh->pipefd[0]);
		dup2(msh->pipefd[1], 1);
		close(msh->pipefd[1]);
		if (execve(get_binary(msh), msh->cmd->arg, msh->env) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		// Parent executing
		pid2 = fork();
		if (pid2 < 0)
		{
			printf("\nCould not fork");
			return (1);
		}
		// Child 2 executing..
		// It only needs to read at the read end
		if (pid2 == 0)
		{
			close(msh->pipefd[1]);
			dup2(msh->pipefd[0], STDIN_FILENO);
			close(msh->pipefd[0]);
			if (execve(get_binary(msh), msh->cmd->arg, msh->env) < 0)
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			// parent executing, waiting for two children
			wait(NULL);
		}
	}
	return (1);
}
