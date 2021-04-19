/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:26:57 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/18 21:05:45 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_full_path(char *path, char *cmd)
{
	char	*tmp;
	char	*bin_cmd;

	tmp = ft_strjoin(path, "/");
	bin_cmd = ft_strjoin(tmp, cmd);
	free(tmp);
	return (bin_cmd);
}

char	*get_binary(t_msh *msh)
{
	char	**split;
	char	*bin;
	int		i;
	int		fd;
	char	*path;
	
	i = -1;
	path = get_env_val("PATH", &(*msh->env));
	split = ft_split(path, ':');
	while (split[++i])
	{
		bin = get_full_path(split[i], msh->cmd->arg[0]);
		fd = open(bin, O_RDONLY);
		if (fd >= 0)
		{
			free_2d(&split);
			close(fd);
			free(path);
			return (ft_strdup(bin));
		}
		close(fd);
		free(bin);
	}
	free(path);
	free_2d(&split);
	return (NULL);
}
