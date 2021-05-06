/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:21:15 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 15:32:28 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shlvl_up(t_msh *msh)
{
	int		level;
	char	*tmp;

	tmp = get_env_val("SHLVL", msh->env);
	level = ft_atoi(tmp);
	level++;
	free(tmp);
	tmp = ft_itoa(level);
	set_env_val(&msh->env, ft_strdup("SHLVL"), tmp);
	free (tmp);
}

int	exec_child(t_msh *msh)
{
	char	*path;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	//tcsetattr(0, TCSANOW, &msh->term);
	path = get_binary(msh, msh->cmd);
	if (!ft_strcmp(path, "./minishell"))
		shlvl_up(msh);
	if (msh->cmd->r_redir || msh->cmd->l_redir || msh->cmd->dbl_r_redir)
		if (!exec_redirect(msh, msh->cmd))
			return (0);
	if (execve(path, msh->cmd->arg, msh->env) < 0)
		exit(execve_error(msh, path, msh->cmd));
	free(path);
	return (1);
}
