/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:24:36 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/16 17:36:00 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_exit(t_msh *msh)
{
	//if (msh->cmd.arg)
	//clear(msh->cmd.arg);
	//if (msh->env)
	//clear(msh->env);
	msh->term.c_lflag |= ECHO;
	msh->term.c_lflag |= ICANON;
	ft_putendl_fd("exit", 1);
	exit (0);
}
