/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:04:29 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/05 16:01:08 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_prompt(t_msh *msh, char *err_msg, t_cmd *cmd)
{
	int		i;
	int		n;
	t_cmd	*cur_cmd;

	cur_cmd = msh->cmd;
	i = 0;
	n = 1;
	msh->fd = 2;
	if (msh->cmd->arg[1])
		n = 2;
	ft_putstr_fd("minishell: ", msh->fd);
	if (cmd)
		cur_cmd = cmd;
	while (i < n)
	{
		ft_putstr_fd(cur_cmd->arg[i++], msh->fd);
		ft_putstr_fd(": ", msh->fd);
	}
	ft_putendl_fd(err_msg, msh->fd);
}

int	ft_error(t_msh *msh, char *msg, t_cmd *cmd_name, int exit_code)
{
	msh->code = exit_code;
	if (msg)
		error_prompt(msh, msg, cmd_name);
	else
		error_prompt(msh, strerror(errno), cmd_name);
	return (0);
}
