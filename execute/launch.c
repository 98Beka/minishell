/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 11:47:25 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	exec_single_cmd(t_msh *msh, char *path)
{
	pid_t pid;

	if (msh->cmd->r_redir > 0)
		dup2(msh->fd, 1);
	if (!get_env_val("PATH", msh->env))
		return (ft_error(msh, "No such file or directory"));
	path = get_binary(msh, msh->cmd);
	if (!path)
		return (ft_error(msh, "command not found"));
	//if ()
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, "123"));
	else if (pid == 0)
	{
		if (execve(path, msh->cmd->arg, msh->env) < 0)
			return (execve_error(msh, path));
	}
	else
		if (waitpid(pid, NULL, 0) < 0)
			return (ft_error(msh, NULL));
	return (1);
}

int	set_fd(t_msh *msh)
{
	msh->fd = 1;
	if (!msh->cmd->arg[1] && msh->cmd->r_redir != 0)
		return (ft_error(msh, "syntax error near unexpected token `newline'"));
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
	return (1);
}

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
			ft_error(msh, "101");
		if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
			ft_error(msh, "11");
		if (close(msh->pfd[i][STDIN_FILENO]) == -1)
			ft_error(msh, "12");
		if (close(msh->pfd[i][STDOUT_FILENO]) == -1)
			ft_error(msh, "13");
	}
}

int	exec_piped_cmd(t_msh *msh, t_cmd *cmnd, char *path, pid_t *pid)
{
	int	i;
	
	i = -1;
	while (cmnd)
	{
		++i;
		if (cmnd->r_redir || cmnd->l_redir || cmnd->dbl_r_redir)
			exec_redirect(msh, cmnd);
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
		{
			set_pfd(msh, i , msh->cmd_count);
			if (execve(path, (cmnd)->arg, msh->env) < 0)
				return (execve_error(msh, path));
		}
		else
		{
			if (i != 0)
			{
				if (close(msh->pfd[i - 1][STDIN_FILENO]) == -1)
					return (ft_error(msh, "14"));
				if (close(msh->pfd[i - 1][STDOUT_FILENO]) == -1)
					return (ft_error(msh, "15"));
			}
			if (waitpid(pid[i], NULL, 0) < 0)
				return (ft_error(msh, NULL));
		}
		cmnd = (cmnd)->next;
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
			ft_error(msh, NULL);
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
