/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:59:24 by ehande            #+#    #+#             */
/*   Updated: 2021/05/05 21:44:02 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_history(t_msh *msh)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(".history", O_RDONLY | O_APPEND | O_CREAT, 0644);
	msh->history = new_2d(0);
	get_next_line(fd, &line);
	while (*line)
	{
		add_l_line(&msh->history, line);
		get_next_line(fd, &line);
	}
	free(line);
}

void	set_history(t_msh *msh)
{
	int	fd;

	add_l_line(&msh->history, ft_strdup(msh->line));
	fd = open(".history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_putendl_fd(msh->line, fd);
	close(fd);
}
