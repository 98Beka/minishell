/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:26:57 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/29 23:52:05 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_arr/ft_arr.h"
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

int	check_cmd(t_msh *msh, char *arg)
{
	struct stat	sb;
	int			fd;

	fd = open(arg, O_RDONLY);
	if (fd >= 0)
	{
		if (fstat(fd, &sb) < 0)
		{
			close(fd);
			return (ft_error(msh, NULL, NULL, 1));
		}
		if (sb.st_mode & S_IFDIR)
			return (ft_error(msh, "is a directory", NULL, 1));
		close(fd);
		return (1);
	}
	return (0);
}

char	*get_binary(t_msh *msh, t_cmd *cmd)
{
	char	**split;
	char	*bin;
	int		i;
	char	*path;

	i = -1;
	if (check_cmd(msh, cmd->arg[0]))
		return (cmd->arg[0]);
	path = get_env_val("PATH", &(*msh->env));
	split = ft_split(path, ':');
	while (split[++i])
	{
		bin = get_full_path(split[i], cmd->arg[0]);
		if (check_cmd(msh, bin))
		{
			free_2d(&split);
			free(path);
			return (bin);
		}
	}
	free(path);
	free_2d(&split);
	return (cmd->arg[0]);
}
