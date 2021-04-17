/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:56:37 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/09 19:14:03 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key(char **env, char *key)
{
	char	*env_key;
	char	*tmp;
	int		i;
	
	i = -1;
	env_key = ft_strjoin(key, "=");
	while (*env)
	{
		tmp = ft_strnstr(*env, env_key, ft_strlen(env_key));
		if (tmp)
		{
			i = tmp - *env;
			free(env_key);
			env_key = (char *)ft_calloc(sizeof(char), ++i);
			if (!env_key)
				return (0);
			while (--i)
				env_key[i] = *env[i];
			return (env_key);
		}
		(*env)++;
	}
	free(env_key);
	return (NULL);
}
