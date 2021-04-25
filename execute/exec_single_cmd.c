/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:42:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/25 12:25:31 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_single_cmd(t_msh *msh, char *path)
{
	pid_t	pid;

	if (!get_env_val("PATH", msh->env))
		return (ft_error(msh, "No such file or directory", NULL));
	path = get_binary(msh, msh->cmd);
	if (!path)
		return (ft_error(msh, "command not found", NULL));
	if (msh->cmd->r_redir || msh->cmd->l_redir || msh->cmd->dbl_r_redir)
		exec_redirect(msh, msh->cmd);
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, "123", NULL));
	else if (pid == 0)
	{
		if (execve(path, msh->cmd->arg, msh->env) < 0)
			return (execve_error(msh, path));
	}
	else
	{
		if (waitpid(pid, NULL, 0) < 0)
			return (ft_error(msh, NULL, NULL));
	}
	return (1);
}
