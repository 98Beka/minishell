/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:32:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 18:49:07 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*path;

	tcap_on(msh);
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, NULL, NULL, 1));
	else if (pid == 0)
	{
		path = get_binary(msh, msh->cmd);
		if (msh->cmd->r_redir || msh->cmd->l_redir || msh->cmd->dbl_r_redir)
			exec_redirect(msh, msh->cmd);
		if (execve(path, msh->cmd->arg, msh->env) < 0)
			exit(execve_error(msh, path));
		free(path);
	}
	else
		if (waitpid(pid, &msh->code, 0) < 0)
			return (ft_error(msh, NULL, NULL, 200));
	tcap_off(msh);
	return (1);
}
