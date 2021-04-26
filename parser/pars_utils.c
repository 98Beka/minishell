/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:30:52 by ehande            #+#    #+#             */
/*   Updated: 2021/04/26 15:17:50 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*last_cmd(t_cmd *cmd)
{
	t_cmd	*p_cmd;

	p_cmd = cmd;
	while (p_cmd->next)
		p_cmd = p_cmd->next;
	return (p_cmd);
}

void	skip_sp_ch(char **line, char ch)
{
	int	i;

	i = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	if ((*line)[i] == ch)
		i++;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	if (i > 0)
		del_to_index(line, i);
}

void	skip_sp(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	if (i > 0)
		del_to_index(line, i);
}

void new_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	(*cmd)->next = NULL;
	(*cmd)->arg = NULL;
	(*cmd)->l_redir = 0;
	(*cmd)->r_redir = 0;
	(*cmd)->dbl_r_redir = 0;
	(*cmd)->pipe = 0;
	(*cmd)->arg = new_2d(0);
	// add_l_line(&(*cmd)->arg, get_arg(msh, line));
	// add_l_line(&(*cmd)->arg, get_arg(msh, line));
}

void	mkline_dlch(char **out, char **line)
{
	make_line(out, **line);
	del_at_index(line, 0);
}
