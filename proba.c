#include "minishell.h"
#include "utils/libft/libft.h"

char	*find_del_key(char ****env, int *s1, char **key)
{
	char	**envp;
	int		i;
	int		del;
	char	*found;

	envp = **env;
	found = NULL;
	i = *s1;
	while (envp[i])
	{
		del = ft_strlen(*key);
		if (((ft_strnstr(envp[i], *key, del)) && (envp[i][del] == '='))
			|| ((ft_strnstr(envp[i], *key, del)) && (envp[i][del]) == '\0'))
				found = envp[i];
		i++;
	}
	*s1 = i;
	return (found);
}

int	del_env_val(char ***env, char *key)
{
	char	**new_env;
	char	*to_del;
	int		s1;
	int		s2;

	s1 = 0;
	new_env = NULL;
	to_del = find_del_key(&env, &s1, &key);
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
		if (ft_strcmp((*env)[s1], to_del))
			new_env[--s2] = ft_strdup((*env)[s1]);
	}
	clear(*env);
	*env = new_env;
	return (1);
}

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

char	*get_binary(t_msh *msh)
{
	char	**split;
	char	*bin;
	int		i;
	int		fd;
	char	*path;
	
	i = -1;
	if (check_cmd(msh, msh->cmd->arg[0]))
		return (ft_strdup(msh->cmd->arg[0]));
	else
	{
		path = get_env_val("PATH", &(*msh->env));
		split = ft_split(path, ':');
		while (split[++i])
		{
			bin = get_full_path(split[i], msh->cmd->arg[0]);
			fd = open(bin, O_RDONLY);
			if (fd >= 0)
			{
				clear(split);
				close(fd);
				free(path);
				return (ft_strdup(bin));
			}
			close(fd);
			free(bin);
		}
		free(path);
		clear(split);
	}
	return (NULL);
}

int	main(void)
{
	char	**arr;

	arr = (char**)malloc(sizeof(char *) * 5);
	arr[0] = ft_strdup("1=One");
	arr[1] = ft_strdup("2=Two");
	arr[2] = ft_strdup("3=Three");
	arr[3] = ft_strdup("4");
	arr[4] = NULL;

	printf("*****\n");
	int	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("*****\n");
	printf("%s\n", get_env_val("4", arr));
	del_env_val(&arr, "4");
	printf("\n*****\n");
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
