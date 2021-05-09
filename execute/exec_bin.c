/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:32:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/09 15:38:45 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/wait.h>

static void	tcap_on(t_msh *msh)
{
	if (!ft_strcmp(msh->cmd->arg[0], "cat"))
	{
		msh->term.c_lflag |= ECHO;
		msh->term.c_lflag |= ICANON;
		tcsetattr(0, TCSANOW, &msh->term);
	}
}

static void	tcap_off(t_msh *msh)
{
	if (!ft_strcmp(msh->cmd->arg[0], "cat"))
	{
		msh->term.c_lflag &= ~(ECHO);
		msh->term.c_lflag &= ~(ICANON);
		tcsetattr(0, TCSANOW, &msh->term);
	}
}

int	exec_bin(t_msh *msh)
{
	pid_t	pid;

	tcap_on(msh);
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, NULL, NULL, 1));
	else if (pid == 0)
		exec_child(msh);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (waitpid(pid, &msh->code, 0) < 0)
			return (ft_error(msh, NULL, NULL, 1));
	}
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	msh->code = WEXITSTATUS(msh->code);
	tcap_off(msh);
	return (1);
}
