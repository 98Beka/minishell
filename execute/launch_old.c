/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/21 11:15:56 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>

int	check_flag(t_msh *msh)
{
	if (msh->cmd->pipe)
	{
		if (pipe(msh->pipefd) < 0)
			ft_error(msh, NULL);
		return (1);
	}
	return (0);
}

void	set_fd(t_msh *msh)
{
	msh->fd = 1;
	//if (!msh->cmd->arg[1] && msh->cmd->r_redir != 0)
	//{
	//	ft_error(msh, "syntax error near unexpected token `newline'");
	//	return ;
	//}
	if (msh->cmd->r_redir < 0)
		msh->fd = 2;
	else if (msh->cmd->r_redir == 1)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL);
	}
	else if (msh->cmd->r_redir == 2)
	{
		msh->fd = open(msh->cmd->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (msh->fd < 0)
			ft_error(msh, NULL);
	}
}

int	num_of_cmds(t_cmd **cmd)
{
	int	i;
	t_cmd *tmp;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	num_of_pipes(t_cmd **cmd)
{
	int	i;
	t_cmd *tmp;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->pipe > 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	launch(t_msh *msh)
{
	char	*path;
	int		i;
	int		j;
	pid_t	pid1;
	t_cmd	*cmd;

	i = num_of_cmds(&msh->cmd);
	j = num_of_pipes(&msh->cmd);
	cmd = msh->cmd;
	path = get_binary(msh);
	if (path)
	{
		while (cmd)
		{
			check_flag(msh);
			set_fd(msh);
			pid1 = fork();
			if (pid1 < 0)
				ft_error(msh, "fork error");
			else if (pid1 == 0)
				exec_child(msh, path);
			else
			{
				close(msh->pipefd[1]);
				wait(&pid1);
			}
			cmd = cmd->next;
		}
	}
	else
		ft_error(msh, "command not foung");
	free(path);
	return (1);
}
