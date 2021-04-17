/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:48:05 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/17 10:34:47 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_cmd_line(t_msh *msh)
{
	(void)msh;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ed", 0), 1, ft_putchar);
}

int	shell_prompt(t_msh *msh)
{
	int		l;
	int		len;
	ssize_t	step;

	step = 0;
	len = 0;
	msh->line = NULL;
	tputs(save_cursor, 1, ft_putchar);
	while (!ft_strnstr(msh->buff, "\n", BUFF_SIZE)
		&& !ft_strnstr(msh->buff, "\4", BUFF_SIZE))
	{
		l = read(0, msh->buff, BUFF_SIZE);
		if (!ft_strncmp(msh->buff, "\e[A", ft_strlen("\e[A")))
		{
			change_cmd_line(msh);
			write(0, "previous in history", 20);
		}
		else if (!ft_strncmp(msh->buff, "\e[B", ft_strlen("\e[B")))
		{
			change_cmd_line(msh);
			write(0, "next in history", 16);
		}
		else if (!ft_strncmp(msh->buff, "\e[C", ft_strlen("\e[C")))
		{
			if (step < len)
			{
				step++;
				tputs(cursor_right, 1, ft_putchar);
			}
		}
		else if (!ft_strncmp(msh->buff, "\e[D", ft_strlen("\e[D")))
		{
			if (step > 0)
			{
				step--;
				tputs(cursor_left, 1, ft_putchar);
			}
		}
		else if (!ft_strncmp(msh->buff, "\177", ft_strlen("\177")))
		{
			if (step > 0)
			{
				step--;
				tputs(cursor_left, 1, ft_putchar);
				del_at_index(&msh->line, len - 1);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
			}
		}
		else if (!ft_strncmp(msh->buff, "\4", ft_strlen("\4")))
			return (0);
		else
			step += write(1, msh->buff, l);
		if (ft_isprint(*msh->buff))
			make_line(&msh->line, *msh->buff);
		len = ft_strlen(msh->line);
	}
	*msh->buff = 0;
	return (1);
}
