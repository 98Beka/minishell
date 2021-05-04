/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:53:50 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/04 12:28:22 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>

static int	parent_do(t_msh *msh, int i, pid_t *pid)
{
	if (i != 0)
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			return (ft_error(msh, NULL, NULL, 1));
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			return (ft_error(msh, NULL, NULL, 1));
	}
	if (waitpid(pid[i], &msh->code, 0) < 0)
		return (ft_error(msh, NULL, NULL, 1));
	return (1);
}

int	child_do(t_msh *msh, t_cmd *cmnd, char *path, int i)
{
	set_pfd(msh, i, msh->cmd_count);
	path = get_binary(msh, cmnd);
	if (cmnd->r_redir || cmnd->l_redir || cmnd->dbl_r_redir)
		exec_redirect(msh, cmnd);
	if (execve(path, (cmnd)->arg, msh->env))
		exit(execve_error(msh, path, cmnd));
	free(path);
	return (1);
}

int	exec_piped_cmd(t_msh *msh, t_cmd *cmnd, pid_t *pid)
{
	int		i;
	char	*path;

	i = -1;
	path = NULL;
	while (cmnd)
	{
		++i;
		pid[i] = fork();
		if (pid[i] == -1)
			return (ft_error(msh, NULL, NULL, 1));
		else if (pid[i] == 0)
			child_do(msh, cmnd, path, i);
		else
			parent_do(msh, i, pid);
		cmnd = (cmnd)->next;
	}
	return (1);
}
