/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:26:57 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/24 11:45:54 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft/libft.h"
#include <sys/_types/_sigaltstack.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

char	*get_full_path(char *path, char *cmd)
{
	char	*tmp;
	char	*bin_cmd;

	tmp = ft_strjoin(path, "/");
	bin_cmd = ft_strjoin(tmp, cmd);
	free(tmp);
	return (bin_cmd);
}

int	check_cmd(t_msh *msh, char *cmd)
{
	struct stat *statbuf;
	int	fd;

	statbuf = NULL;
	fd = open(cmd, O_RDONLY);
	if (fd >= 0)
	{
		if (fstat(fd, statbuf) < 0)
		{
			close(fd);
			return (ft_error(msh, NULL));
		}
		close(fd);
	}
	return (1);
}

char	*get_binary(t_msh *msh, t_cmd *cmd)
{
	char	**split;
	char	*bin;
	int		i;
	int		fd;
	char	*path;
	
	i = -1;
	path = get_env_val("PATH", &(*msh->env));
	if (!check_cmd(msh, path))
		return (NULL);
	split = ft_split(path, ':');
	while (split[++i])
	{
		bin = get_full_path(split[i], cmd->arg[0]);
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
