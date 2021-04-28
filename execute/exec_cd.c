/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:23:20 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 18:07:42 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_cd_home(t_msh *msh)
{
	char	*value;

	value = get_env_val("HOME", msh->env);
	if (!value)
		return (0);
	set_env_val(&msh->env, ft_strdup("PWD"), value);
	if (chdir(value) < 0)
		ft_error(msh, NULL, NULL, 1);
	free(value);
	return (1);
}

int	change_dir(t_msh *msh, char *value, char *tmp)
{
	if (chdir(value) < 0)
	{
		free(value);
		free(tmp);
		return (ft_error(msh, NULL, NULL, 1));
	}
	set_env_val(&msh->env, ft_strdup("PWD"), value);
	set_env_val(&msh->env, ft_strdup("OLDPWD"), tmp);
	ft_putendl_fd(value, 1);
	return (1);
}

int	exec_cd_previous_dir(t_msh *msh)
{
	char	*value;
	char	*tmp;

	tmp = getenv("PWD");
	if (!getcwd(tmp, BUFF_SIZE))
		return (ft_error(msh, NULL, NULL, 1));
	value = get_env_val("OLDPWD", msh->env);
	if (!ft_strcmp(msh->cmd->arg[1], "-"))
	{
		free(msh->cmd->arg[1]);
		msh->cmd->arg[1] = ft_strdup("OLDPWD");
	}
	if (!value)
		printf("%s: %s: %s not set\n", msh->shell_name, msh->cmd->arg[0],
			msh->cmd->arg[1]);
	else
	{
		if (!change_dir(msh, value, tmp))
			return (0);
	}
	free_2d(&(msh->cmd->arg));
	free(value);
	return (1);
}

int	exec_cd_dir(t_msh *msh)
{
	if (chdir(msh->cmd->arg[1]) < 0)
	{
		msh->code = 1;
		ft_error(msh, NULL, NULL, 1);
	}
	else
	{
		getcwd(msh->buff, BUFF_SIZE);
		set_env_val(&msh->env, ft_strdup("PWD"), msh->buff);
	}
	return (1);
}

int	exec_cd(t_msh *msh)
{
	char	*value;

	msh->code = 0;
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
			return (ft_error(msh, NULL, NULL, 1));
		set_env_val(&msh->env, ft_strdup("OLDPWD"), value);
		exec_cd_dir(msh);
	}
	free (value);
	return (1);
}
