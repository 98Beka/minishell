/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/22 12:55:29 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <unistd.h>

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
	if (!msh->cmd->arg[1] && msh->cmd->r_redir != 0)
	{
		ft_error(msh, "syntax error near unexpected token `newline'");
		return ;
	}
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
	int		i;
	t_cmd	*tmp;

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
	int		i;
	t_cmd	*tmp;

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
	int		*pfd[2];
	pid_t	*pid;
	char	*path;
	int		i;
	t_cmd	*cmd;

	pid = NULL;
	cmd = msh->cmd;



	i = -1;
	int		cmd_num;
	int		pip_num;
	cmd_num = num_of_cmds(&msh->cmd);
	pip_num = num_of_pipes(&msh->cmd);
	//pip_num = 2;
	*pfd = (int *)malloc(sizeof(int) * pip_num);
	while (++i < pip_num)
	{
		if (pipe(pfd[i]) < 0)
			ft_error(msh, NULL);
	}
	
	pid = (pid_t *)ft_calloc(sizeof(pid_t), cmd_num);
	//	i = -1;
	//while (++i < cmd_num)
	//{
	//	pid[i] = fork();
	//	if (pid[i] == -1)
	//		ft_error(msh, NULL);
	//}
	path = get_binary(msh, cmd);
	i = 0;
	//if (path)
	//{
		pid[i] = fork();
		while (cmd)
		{
			if (cmd->pipe)
			{
				path = get_binary(msh, msh->cmd);
				if (pid[i] < 0)
					ft_error(msh, "1");
				else if (pid[i] == 0)
				{
					if (i == 0)	// FIRST CHILD
					{
						if (close(pfd[i][0]) == -1)
							ft_error(msh, "2");
						if (dup2(pfd[i][1], STDOUT_FILENO) == -1)
							ft_error(msh, "3");
						if (close(pfd[i][1]) == -1)
							ft_error(msh, "4");
					}
					else if (i == cmd_num - 1)	// LAST CHILD
					{
						if (dup2(pfd[i - 1][0], STDIN_FILENO) == -1)
							ft_error(msh, "5");
						if (close(pfd[i - 1][0]) == -1)
							ft_error(msh, "6");
						if (close(pfd[i - 1][1]) == -1)
							ft_error(msh, "7");
					}
					else 	// MIDDLE CHILD
					{
						if (dup2(pfd[i - 1][0], STDIN_FILENO) == -1)
							ft_error(msh, "8");
						if (close(pfd[i][0]) == -1)
							ft_error(msh, "9");
						if (close(pfd[i - 1][0]) == -1)
							ft_error(msh, "10");
						if (dup2(pfd[i][1], STDOUT_FILENO) == -1)
							ft_error(msh, "11");
						if (close(pfd[i][1]) == -1)
							ft_error(msh, "12");
					}
					if (execve(path, msh->cmd->arg, msh->env) < 0)
						ft_error(msh, "13");
				}
				else
				{
					waitpid(pid[i], NULL, 0);
					if (msh->cmd->pipe)
					{
						i++;
						pid[i] = fork();
					}
				}
			}	
			else
			{
				if (pid[i] == 0)
				{
					if (execve(path, cmd->arg, msh->env) < 0)
						ft_error(msh, "13");
				}
				else
					waitpid(pid[i], NULL, 0);
			}
			//free(path);
			cmd = cmd->next;
		}
	//}
	//else
	//{
	//	ft_error(msh, "command not foung");
	//	free(path);
	//}
	//free(path);
	//i = -1;
	//while (++i < cmd_num)
	//{
	//		if (waitpid (pid[i], NULL, 0) == -1)
	//			ft_error(msh, NULL);
	//}
	




	
	//path = get_binary(msh);
	//if (path)
	//{
	//	while (cmd)
	//	{
	//		check_flag(msh);
	//		set_fd(msh);
	//		pid1 = fork();
	//		if (pid1 < 0)
	//			ft_error(msh, "fork error");
	//		else if (pid1 == 0)
	//			exec_child(msh, path);
	//		else
	//		{
	//			close(msh->pipefd[1]);
	//			wait(&pid1);
	//		}
	//		cmd = cmd->next;
	//	}
	//}
	//else
	//	ft_error(msh, "command not foung");
	return (1);
}
