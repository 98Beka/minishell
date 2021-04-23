/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:23:47 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/19 22:07:01 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_value(char *var, char *key)
{
	int		len;
	
	len = ft_strlen(key);
	if (((ft_strnstr(var, key, len)) && (var[len] == '='))
		|| ((ft_strnstr(var, key, len)) && (var[len]) == '\0'))
			return (var);
	return (NULL);
}

char	*get_env_val(char *key, char **env)
{
	char	**tmp;
	char	*arg;
	int		i;

	i = 0;
	while (env[i])
	{
		if ((is_value(env[i], key)))
		{
			if (!ft_strchr(env[i], '='))
				return (NULL);
			tmp = ft_split(env[i], '=');
			arg = ft_strdup(tmp[1]);
			clear(tmp);
			return (arg);
		}
		i++;
	}
	return (NULL);
}
