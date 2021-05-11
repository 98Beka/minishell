/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:07:52 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/11 21:00:41 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arrdup(char **env)
{
	char	**dup;
	int		i;

	i = 0;
	while (env[i])
		i++;
	dup = (char **)ft_calloc(sizeof(char *), ++i);
	if (!dup)
		return (NULL);
	i = -1;
	while (env[++i])
		dup[i] = ft_strdup(env[i]);
	return (dup);
}

void	printf_fd(int fd, t_msh *msh, char *split0, char *split1)
{
	if (msh->flag)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(split0, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(split1, fd);
		if (!msh->exp_pipe)
			ft_putendl_fd("\"", fd);
		else
		{
			ft_putstr_fd("\"", fd);
			ft_putendl_fd("$", fd);
		}
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(split0, fd);
	}
}

int	declare(t_msh *msh, char ***env)
{
	int		i;
	char	**dup;
	char	**split;

	dup = ft_arrdup(*env);
	i = -1;
	sort_envp(&dup);
	while (dup[++i])
	{
		split = ft_split(dup[i], '=');
		msh->flag = ft_strchr(dup[i], '=');
		printf_fd(msh->fd, msh, split[0], split[1]);
		free_2d(&split);
	}
	free_2d(&dup);
	return (1);
}

int	exec_export(t_msh *msh)
{
	char	**var;

	var = NULL;
	if (msh->cmd->arg[1] == NULL)
		return (declare(msh, &msh->env));
	else
	{
		if (ft_strchr(msh->cmd->arg[1], '='))
		{
			var = ft_split(msh->cmd->arg[1], '=');
			if (var[1] == NULL)
				add_l_line(&var, ft_strdup(""));
			set_env_val(&msh->env, ft_strdup(var[0]), var[1]);
			free_2d(&var);
		}
		else
			set_env_val(&msh->env, ft_strdup(msh->cmd->arg[1]), NULL);
	}
	return (1);
}
