/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:26:01 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/04 17:54:50 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//get environment value
// char	*get_env_val(char *key, char **env)
// {
// 	char	**tmp;
// 	char	*arg;
// 	char	*key_in;
// 	int		i;

// 	i = -1;
// 	while (env[++i])
// 	{
// 		key_in = ft_strjoin(key, "=");
// 		tmp = ft_split(env[i], '=');
// 		if (!ft_strncmp(key, tmp[0], ft_strlen(key_in)))
// 		{
// 			free(key_in);
// 			arg = ft_strdup(tmp[1]);
// 			clear(tmp);
// 			return (arg);
// 		}
// 		free(key_in);
// 		clear(tmp);
// 	}
// 	return (NULL);
// }

// int		del_env_val(char ***env, char *key)
// {
// 	char	**new_env;
// 	char	*tmp;
// 	char	*to_del;
// 	int		size1;
// 	int		size2;

// 	size1 = 0;
// 	to_del = NULL;
// 	new_env = NULL;
// 	tmp = ft_strjoin(key, "=");
// 	while ((*env)[size1])
// 	{
// 		if (!ft_strncmp((*env)[size1], tmp, ft_strlen(tmp)))
// 			to_del = ft_strnstr((*env)[size1], tmp, ft_strlen(tmp));
// 		size1++;
// 	}
// 	if (to_del)
// 	{
// 		new_env = (char **)ft_calloc(sizeof(char *), size1);
// 		if (!new_env)
// 			return (0);
// 	}
// 	else
// 		return (1);
// 	size2 = size1 - 1;
// 	while (--size1 >= 0)
// 	{
// 		if (!ft_strncmp((*env)[size1], tmp, ft_strlen(tmp)))
// 			continue ;
// 		else
// 			new_env[--size2] = ft_strdup((*env)[size1]);
// 	}
// 	free(tmp);
// 	clear(*env);
// 	*env = new_env;
// 	return (1);
// }

// int		reset_variable(char **env, char *tmp, char *value)
// {
// 	char	*variable;
	
// 	variable = *env;
// 	*env = ft_strjoin(tmp, value);
// 	free (tmp);
// 	free (variable);
// 	return (1);
// }

// int		set_env_val(char ***env, char *key, char *value)
// {
// 	char	**new_env;
// 	char	*tmp;
// 	int		i;

// 	i = -1;
// 	new_env = NULL;
// 	tmp = ft_strjoin(key, "=");
// 	while ((*env)[++i])
// 		if (ft_strnstr((*env)[i], tmp, ft_strlen(tmp)))
// 			return (reset_variable(&(*env)[i], tmp, value));
// 	i += 2;
// 	new_env = (char **)ft_calloc(sizeof(char *), (i--));
// 	if (!new_env)
// 		return (0);
// 	new_env[--i] = ft_strjoin(tmp, value);
// 	free(tmp);
// 	while (--i >= 0)
// 		new_env[i] = ft_strdup((*env)[i]);
// 	clear(*env);
// 	*env = new_env;
// 	return (1);
// }

// int		get_envp(char **envp, t_msh *msh)
// {
// 	int	 i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	msh->env = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!msh->env)
// 		return (0);
// 	envp[i] = NULL;
// 	while (envp[--i])
// 		msh->env[i] = ft_strdup(envp[i]);
// 	return (1);
// }
