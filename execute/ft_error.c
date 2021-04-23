/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:04:29 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/23 15:04:43 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_prompt(t_msh *msh, char *err_msg)
{
	int		i;
	int		n;

	i = 0;
	n = 1;
	msh->fd = 2;
	if (msh->cmd->arg[1])
		n = 2;
	ft_putstr_fd("minishell: ", msh->fd);
	while (i < n)
	{
		ft_putstr_fd(msh->cmd->arg[i++], msh->fd);
		ft_putstr_fd(": ", msh->fd);
	}
	ft_putendl_fd(err_msg, msh->fd);
}

int	ft_error(t_msh *msh, char *msg)
{
	if (msg)
		error_prompt(msh, msg);
	else
		error_prompt(msh, strerror(errno));
	return (1);
}
