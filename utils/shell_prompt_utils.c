/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 03:41:14 by ehande            #+#    #+#             */
/*   Updated: 2021/04/30 02:13:37 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_cmd_line(t_msh *msh)
{
	(void)msh;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ed", 0), 1, ft_putchar);
}

void	del_cap(t_msh *msh, int len)
{
	tputs(cursor_left, 1, ft_putchar);
	del_at_index(&msh->line, len - 1);
	tputs(tgetstr("dc", 0), 1, ft_putchar);
}

void	clean_console(t_msh *msh, int *len)
{
	while ((*len)--)
		del_cap(msh, *len);
}
