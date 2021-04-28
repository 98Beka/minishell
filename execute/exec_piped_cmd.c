/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:53:50 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 18:10:20 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>

static void	close_fd(t_msh *msh, int i, int cmd)
{
	if (i == 0)
	{
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, "1", NULL, 1);
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, "3", NULL, 1);
	}
	else if (i == cmd - 1)
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, "4", NULL, 1);
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, "5", NULL, 1);
	}
	else
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, "6", NULL, 1);
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, "7", NULL, 1);
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, "8", NULL, 1);
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, "9", NULL, 1);
	}
}

void	set_pfd(t_msh *msh, int i, int cmd)
{
	if (i == 0)
	{
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, "10", NULL, 1);
	}
	else if (i == cmd - 1)
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, "11", NULL, 1);
	}
	else
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, "12", NULL, 1);
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, "13", NULL, 1);
	}
	close_fd(msh, i, cmd);
}

static int	parent_do(t_msh *msh, int i, pid_t *pid)
{
	if (i != 0)
	{
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			return (ft_error(msh, "14", NULL, 1));
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			return (ft_error(msh, "15", NULL, 1));
	}
	if (waitpid(pid[i], &msh->code, 0) < 0)
		return (ft_error(msh, "16", NULL, 1));
	return (1);
}

int	child_do(t_msh *msh, t_cmd *cmnd, char *path, int i)
{
	set_pfd(msh, i, msh->cmd_count);
	path = get_binary(msh, cmnd);
	if (!path)
		return (ft_error(msh, "command not found", cmnd, 127));
	if (cmnd->r_redir || cmnd->l_redir || cmnd->dbl_r_redir)
		exec_redirect(msh, cmnd);
	if (execve(path, (cmnd)->arg, msh->env))
		return (execve_error(msh, path));
	free(path);
	return (1);
}

int	exec_piped_cmd(t_msh *msh, t_cmd *cmnd, char *path, pid_t *pid)
{
	int	i;

	i = -1;
	while (cmnd)
	{
		++i;
		pid[i] = fork();
		if (pid[i] == -1)
			return (ft_error(msh, "0", NULL, 1));
		else if (pid[i] == 0)
			child_do(msh, cmnd, path, i);
		else
			parent_do(msh, i, pid);
		cmnd = (cmnd)->next;
	}
	return (1);
}
