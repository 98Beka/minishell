/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:20:44 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 21:15:51 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	reset_variable(char **env, char *key, char *value)
{
	char	*variable;
	char	*temp;

	variable = *env;
	if (value)
	{
		temp = ft_strjoin(key, "=");
		*env = ft_strjoin(temp, value);
		free(temp);
	}
	else
		*env = ft_strdup(key);
	free (key);
	free (variable);
	return (1);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if ((key[i] == ' ') || (ft_isalpha(key[i])))
	{
		while (key[++i])
		{
			if (key[i] != ' ' && !ft_isalpha(key[i]) && !ft_isdigit(key[i]))
			{
				printf("minishell: export: `%s': not a valid identifier\n", key);
				free(key);
				return (0);
			}
		}
	}
	else
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		return (0);
	}
	return (1);
}

int	find_key(char ***env, char *key, int *i)
{
	int	j;

	j = *i;
	while ((*env)[++j])
	{
		if ((ft_strnstr((*env)[j], key, ft_strlen(key))
			&& (*env)[j][ft_strlen(key)] == '=')
			|| (ft_strnstr((*env)[j], key, ft_strlen(key))
			&& (*env)[j][ft_strlen(key)] == '\0'))
		{
			*i = j;
			return (1);
		}
	}
	*i = j;
	return (0);
}

static void	set_key(char **tmp, char *key, char *value)
{
	if (value)
		*tmp = ft_strjoin(key, "=");
	else
		*tmp = ft_strdup(key);
}

int	set_env_val(char ***env, char *key, char *value)
{
	char	**new_env;
	char	*tmp;
	int		i;

	i = -1;
	if (!check_key(key))
		return (1);
	if (find_key(env, key, &i))
		return (reset_variable(&(*env)[i], key, value));
	set_key(&tmp, key, value);
	i += 2;
	new_env = (char **)ft_calloc(sizeof(char *), (i--));
	if (!new_env)
		return (0);
	if (value)
		new_env[--i] = ft_strjoin(tmp, value);
	else
		new_env[--i] = ft_strdup(tmp);
	free(tmp);
	while (--i >= 0)
		new_env[i] = ft_strdup((*env)[i]);
	free_2d(env);
	*env = new_env;
	free(key);
	return (1);
}
