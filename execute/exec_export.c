/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:07:52 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 21:39:05 by hveiled          ###   ########.fr       */
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

void	printf_fd(int fd, char *flag, char *split0, char *split1)
{
	if (flag)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(split0, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(split1, fd);
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
	char	*flag;

	dup = ft_arrdup(*env);
	i = -1;
	sort_envp(&dup);
	while (dup[++i])
	{
		split = ft_split(dup[i], '=');
		flag = ft_strchr(dup[i], '=');
		printf_fd(msh->fd, flag, split[0], split[1]);
		clear(split);
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
				var[1] = ft_strdup("");
			set_env_val(&msh->env, var[0], var[1]);
		}
		else
			set_env_val(&msh->env, msh->cmd->arg[1], NULL);
	}
	return (1);
}
