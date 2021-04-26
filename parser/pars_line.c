/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:39:49 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/26 14:27:28 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pip(t_msh *msh, char **line)
{
	msh->cmd->pipe = 1;
	skip_sp_ch(line, '|');
	new_cmd(msh, &(last_cmd(msh->cmd)->next), line);
}

static void	redir(t_msh *msh, char **line, int *dir, char ch)
{
	*dir = 1;
	skip_sp_ch(line, ch);
	last_cmd(msh->cmd)->file = get_arg(msh, line);
}

int	pars_line(t_msh *msh, char **line)
{
	new_cmd(msh, &msh->cmd, line);
	while (*line && **line && **line != ';')
	{
		if (**line == '|')
			pip(msh, line);
		else if (**line == '<' || **line == '>')
		{
			if ((*line)[0] == '<')
				redir(msh, line, &(last_cmd(msh->cmd)->l_redir), '<');
			else
				redir(msh, line, &(last_cmd(msh->cmd)->r_redir), '>');
			break ;
		}
		else
			add_l_line(&(msh->cmd)->arg, get_arg(msh, line));
	}
	return (1);
}
