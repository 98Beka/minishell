/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:23:20 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 15:31:15 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_cd_home(t_msh *msh)
{
	char	*value;
	
	value = get_env_val("HOME", msh->env);
	if (!value)
		return (0);
	set_env_val(&msh->env, ft_strdup("PWD"), value);
	if (chdir(value) < 0)
		ft_error(msh, NULL, NULL);
	free(value);
	return (1);
}

int		exec_cd_previous_dir(t_msh *msh)
{
	char	*value;
	char	*tmp;
	
	tmp = getenv("PWD");
	if (!getcwd(tmp, BUFF_SIZE))
		return (ft_error(msh, NULL, NULL));
	value = get_env_val("OLDPWD", msh->env);
	//printf("%s\n", value);
	//printf("%s\n", msh->cmd->arg[0]);
	//printf("%s\n", msh->cmd->arg[1]);
	if (!ft_strcmp(msh->cmd->arg[1], "-"))
	{
		free(msh->cmd->arg[1]);
		msh->cmd->arg[1] = ft_strdup("OLDPWD");
	}
	if (!value)
		printf("%s: %s: %s not set\n", msh->shell_name, msh->cmd->arg[0], msh->cmd->arg[1]);
	else
	{
		if (chdir(value) < 0)
		{
			free(value);
			free(tmp);
			return (ft_error(msh, NULL, NULL));
		}
		set_env_val(&msh->env, ft_strdup("PWD"), value);
		set_env_val(&msh->env, ft_strdup("OLDPWD"), tmp);
		ft_putendl_fd(value, 1);
	}
	free_2d(&(msh->cmd->arg));
	free(value);
	return (1);
}

int		exec_cd_dir(t_msh *msh)
{
	if (chdir(msh->cmd->arg[1]) < 0)
		ft_error(msh, NULL, NULL);
	else
	{
		getcwd(msh->buff, BUFF_SIZE);
		set_env_val(&msh->env, ft_strdup("PWD"), msh->buff);
	}
	return (1);
}

int		exec_cd(t_msh *msh)
{
	char	*value;

	value = NULL;
	value = get_env_val("PWD", msh->env);
	if (!ft_strcmp(msh->cmd->arg[1], "--") || !ft_strcmp(msh->cmd->arg[1], "~")
		|| !msh->cmd->arg[1])
		{
			set_env_val(&msh->env, ft_strdup("OLDPWD"), value);
			exec_cd_home(msh);
		}
	else if (!ft_strcmp(msh->cmd->arg[1], "-"))
		exec_cd_previous_dir(msh);
	else
	{
		if (!getcwd(value, BUFF_SIZE))
			return (ft_error(msh, NULL, NULL));
		set_env_val(&msh->env, ft_strdup("OLDPWD"), value);
		exec_cd_dir(msh);
	}
	free (value);
	return (1);
}
