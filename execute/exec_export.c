/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:07:52 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/18 21:06:50 by ehande           ###   ########.fr       */
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

int	declare(char ***env)
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
		if (ft_strchr(dup[i], '='))
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		else
			printf("declare -x %s\n", split[0]);
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
		return (declare(&msh->env));
	// else if (!check_key(msh->cmd->arg[1]))
	// 	return (1);
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
