/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:18:24 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 13:31:52 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch(t_msh *msh)
{
	char	*path;
	pid_t	pid;
	t_cmd	*cmd;
	
	cmd = msh->cmd;
	path = get_binary(msh);
	if (path)
	{
		while (cmd)
		{
			pid = fork();
			if (pid == 0)
				exec_child(msh, path);
			else if (pid < 0)
				ft_error(msh, "fork error");
			else
				wait(&pid);
			cmd = cmd->next;
		}
	}
	else
		ft_error(msh, "command not foung");
	free(path);
	return (1);
}
