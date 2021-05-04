/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/04 10:12:05 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_error(msh, NULL, NULL, 1);
	}
	return (1);
}

void	free_msh(t_msh *msh, pid_t *pid)
{
	t_cmd	*p;
	int		i;

	i = msh->pipe_count;
	if (pid)
		free(pid);
	if (msh->pfd)
	{
		while (i--)
			free(msh->pfd[i]);
		free(msh->pfd);
	}
	while (msh->cmd)
	{
		p = msh->cmd;
		
		free_2d(&p->arg);
		if (p->file)
			free(p->file);
		msh->cmd = msh->cmd->next;
		free(p);
	}
	
	new_cmd(&msh->cmd);
}

int	launch(t_msh *msh)
{
	pid_t	*pid;
	int		i;

	pid = NULL;
	if (!prepare_data(msh, &pid))
		return (1);
	if (!ft_strcmp(msh->cmd->arg[0], "cat"))
		g_process_flag = 1;
	i = -1;
	if (msh->pipe_count != 0)
	{
		if (!exec_piped_cmd(msh, msh->cmd, pid))
			return (1);
	}
	else
		exec_single_cmd(msh);

	free_msh(msh, pid);
	return (1);
}
