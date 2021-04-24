/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:24:36 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 15:31:42 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric_arg(char	*arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

int	exec_exit(t_msh *msh)
{
	int		ret;

	ret = 0;
	ft_putendl_fd("exit", 1);
	if (msh->cmd->arg[1])
	{
		if (!is_numeric_arg(msh->cmd->arg[1]))
			ft_error(msh, "numeric argument required", NULL);
		else
			ret = ft_atoi(msh->cmd->arg[1]);
	}
	if (msh->cmd->arg)
		clear(msh->cmd->arg);
	if (msh->env)
		clear(msh->env);
	msh->term.c_lflag |= ECHO;
	msh->term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &msh->term);
	exit(ret);
}
