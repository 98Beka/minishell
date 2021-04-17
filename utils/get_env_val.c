/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:23:47 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/09 15:24:03 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_val(char *key, char **env)
{
	char	**tmp;
	char	*arg;
	char	*key_in;
	int		i;

	i = -1;
	while (env[++i])
	{
		key_in = ft_strjoin(key, "=");
		tmp = ft_split(env[i], '=');
		if (!ft_strncmp(key, tmp[0], ft_strlen(key_in)))
		{
			free(key_in);
			arg = ft_strdup(tmp[1]);
			clear(tmp);
			return (arg);
		}
		free(key_in);
		clear(tmp);
	}
	return (NULL);
}
