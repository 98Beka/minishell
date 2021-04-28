/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:42:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 12:36:41 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

static char	*in_env(t_msh *msh, char *key)
{
	int	i;
	int	len;
	
	i = -1;
	while (msh->env[++i])
	{
		len = ft_strlen(key);
		if (((ft_strnstr(msh->env[i], key, len))
			&& (msh->env[i][len] == '='))
			|| ((ft_strnstr(msh->env[++i], key, len))
			&& (msh->env[i][len]) == '\0'))
				return (msh->env[i]);
	}
	return (NULL);
}

int	exec_single_cmd(t_msh *msh, char *path)
{
	pid_t	pid;

	if (!in_env(msh, "PATH"))
		return (ft_error(msh, "No such file or directory", NULL));
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, "123", NULL));
	else if (pid == 0)
	{
		path = get_binary(msh, msh->cmd);
		if (!path)
		{
			msh->code = 127;
			return (ft_error(msh, "command not found", NULL));
		}
		if (msh->cmd->r_redir || msh->cmd->l_redir || msh->cmd->dbl_r_redir)
			exec_redirect(msh, msh->cmd);
		if (execve(path, msh->cmd->arg, msh->env) < 0)
			return (execve_error(msh, path));
	}
	else
	{
		//close(msh->fd);
		if (waitpid(pid, &msh->code, 0) < 0)
			return (ft_error(msh, NULL, NULL));
	}
	return (1);
}
