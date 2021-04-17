/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 20:24:26 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 13:30:17 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_bin(t_msh *msh)
{
    pid_t	pid;
	char	*path;

    pid = fork();
	path = get_binary(msh);
    if (pid == -1)
	{
        ft_error(msh, NULL);
        //free(path);
        return (1);
    }
	else if (pid == 0)
	{
        if (execve(path, msh->cmd->arg, msh->env) < 0)
        {
            //free(path);
            return (0);
        }
        //free(path);
        exit(0);
    }
	else
	{
        wait(NULL); 
        //free(path);
        return (1);
    }
}
