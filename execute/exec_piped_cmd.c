/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:53:50 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/23 18:01:07 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/_types/_pid_t.h>

static void	set_pfd(t_msh *msh, int	i, int cmd)
{
	if (i == 0)
	{
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, "2");
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, "3");
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, "4");
	}
	else if (i == cmd - 1)
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, "5");
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, "6");
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, "7");
	}
	else
	{
		if (dup2(msh->pfd[i - 1][STDIN_FILENO], STDIN_FILENO) == -1)
			ft_error(msh, "8");
		if (dup2(msh->pfd[i][STDOUT_FILENO], STDOUT_FILENO) == -1)
			ft_error(msh, "9");
		if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
			ft_error(msh, "10");
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, "11");
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, "12");
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, "13");
	}
}

static int	parent_do(t_msh *msh, int *i, pid_t **pid)
{
	if (*i != 0)
	{
		if (close(msh->pfd[*i - 1][STDIN_FILENO]) == -1)
			return (ft_error(msh, "14"));
		if (close(msh->pfd[*i - 1][STDOUT_FILENO]) == -1)
			return (ft_error(msh, "15"));
	}
	if (waitpid(*pid[*i], NULL, 0) < 0)
		return (ft_error(msh, NULL));
	return (1);
}

int	child_do(t_msh *msh, t_cmd *cmnd, char *path, int *i)
{
	set_pfd(msh, *i, msh->cmd_count);
	if (execve(path, (cmnd)->arg, msh->env))
		return (ft_error(msh, NULL));
}

int	exec_piped_cmd(t_msh *msh, t_cmd *cmnd, char *path, pid_t *pid)
{
	int	i;

	i = -1;
	while (cmnd)
	{
		++i;
		path = get_binary(msh, cmnd);
		if (!path)
		{
			free(path);
			return (ft_error(msh, "command not found"));
		}
		pid[i] = fork();
		if (pid[i] == -1)
			return (ft_error(msh, "0"));
		else if (pid[i] == 0)
			child_do(msh, cmnd, path, &i);
		else
			parent_do(msh, &i, &pid);
		cmnd = (cmnd)->next;
	}
	return (1);
}
