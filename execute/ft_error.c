/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:04:29 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 13:32:12 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_prompt(t_msh *msh, char *err_msg)
{
	int		i;
	int		n;

	i = -1;
	n = 1;
	ft_putstr_fd("minishell: ", 2);
	while (++i < n)
	{
		if (!ft_strcmp(msh->cmd->arg[i], "-"))
			msh->cmd->arg[i] = get_env_val("OLDPWD", msh->env);
		ft_putstr_fd(msh->cmd->arg[i], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg, 2);
}

int	ft_error(t_msh *msh, char *msg)
{
	if (msg)
		error_prompt(msh, msg);
	else
		error_prompt(msh, strerror(errno));
	return (0);
}
