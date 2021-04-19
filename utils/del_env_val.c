/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:21:48 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/18 21:05:05 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_del_key(char ****env, int *s1, char **key)
{
	char	**envp;
	int		i;
	int		del;

	envp = **env;
	i = *s1;
	while (envp[i])
	{
		del = ft_strlen(*key);
		if ((ft_strnstr(envp[i], *key, del) && envp[i][del] == '=')
			|| (ft_strnstr(envp[i], *key, del) && envp[i][del]) == '\0')
			return (envp[i]);
		i++;
	}
	*s1 = i;
	return (NULL);
}

int	del_env_val(char ***env, char *key)
{
	char	**new_env;
	char	*to_del;
	int		s1;
	int		s2;

	s1 = 0;
	new_env = NULL;
	// to_del = find_del_key(&env, &s1, &key);
	while ((*env)[s1])
	{
		if ((ft_strnstr((*env)[s1], key, ft_strlen(key))
			&& (*env)[s1][ft_strlen(key)] == '=')
			|| (ft_strnstr((*env)[s1], key, ft_strlen(key))
			&& (*env)[s1][ft_strlen(key)] == '\0'))
			to_del = (*env)[s1];
		s1++;
	}
	if (!to_del)
		return (1);
	else
	{
		new_env = (char **)ft_calloc(sizeof(char *), (s1));
		if (!new_env)
			return (0);
	}
	s2 = s1 - 1;
	while (--s1 >= 0)
	{
		if (!ft_strcmp((*env)[s1], to_del))
			continue ;
		else
			new_env[--s2] = ft_strdup((*env)[s1]);
	}
	free_2d(env);
	*env = new_env;
	return (1);
}
