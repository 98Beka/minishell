/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 21:44:18 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_fd(t_msh *msh)
{
	msh->fd = 1;
	if (!msh->cmd->arg[1] && msh->cmd->r_redir != 0)
		return (ft_error(msh, "syntax error unexpected token `newline'", NULL));
	if (msh->cmd->r_redir < 0)
		msh->fd = 2;
	else if (msh->cmd->r_redir == 1)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL, NULL);
	}
	else if (msh->cmd->r_redir == 2)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL, NULL);
	}
	return (1);
}

static int	num_of_cmds(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->arg[0])
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	num_of_pipes(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->pipe)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	prepare_data(t_msh *msh, pid_t **pid)
{
	int	i;

	msh->cmd_count = num_of_cmds(&msh->cmd);
	msh->pipe_count = num_of_pipes(&msh->cmd);
	msh->pipe_count = msh->cmd_count - 1;
	msh->pfd = (int **)malloc(sizeof(int *) * (msh->cmd_count - 1));
	if (!msh->pfd)
		return (0);
	i = -1;
	while (++i < msh->cmd_count - 1)
		msh->pfd[i] = (int *)malloc(sizeof(int) * 2);
	*pid = (pid_t *)malloc(sizeof(pid) * msh->cmd_count);
	if (!*pid)
		return (0);
	i = -1;
	while (++i < msh->pipe_count)
	{
		if (pipe(msh->pfd[i]) == -1)
			ft_error(msh, NULL, NULL);
	}
	return (1);
}

int	launch(t_msh *msh)
{
	pid_t	*pid;
	int		i;
	char	*path;

	path = NULL;
	if (!prepare_data(msh, &pid))
		return (1);
	i = -1;
	if (msh->pipe_count != 0)
	{
		if (!exec_piped_cmd(msh, msh->cmd, path, pid))
			return (1);
	}
	else
		exec_single_cmd(msh, path);
	free (path);
	return (1);
}
