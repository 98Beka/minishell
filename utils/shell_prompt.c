/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:48:05 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/03 21:12:10 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	up_down(t_msh *msh, char *bf, int *len, ssize_t *stp)
{
	char	*tmp;

	clean_console(msh, len);
	tputs(restore_cursor, 1, ft_putchar);
	if (!ft_strncmp(bf, "\e[A", 3))
	{
		if (msh->h_index)
			msh->h_index -=1;
		tmp = msh->history[msh->h_index];
	}
	if (!ft_strncmp(bf, "\e[B", 3))
	{
		if (msh->history[msh->h_index + 1])
			msh->h_index +=1;
		tmp = msh->history[msh->h_index];
	}
	*stp = write(0, tmp, ft_strlen(tmp));
	free(msh->line);
	msh->line = ft_strdup(tmp);
	*len = ft_strlen(tmp);
}

void	right_left_del(t_msh *msh, ssize_t *stp, int len, char *bf)
{
	if (!ft_strncmp(bf, "\e[C", 3))
	{
		if (*stp < len)
		{
			(*stp)++;
			tputs(cursor_right, 1, ft_putchar);
		}
	}
	if (!ft_strncmp(bf, "\e[D", 3))
	{
		if (*stp > 0)
		{
			(*stp)--;
			tputs(cursor_left, 1, ft_putchar);
		}
	}
	if (!ft_strncmp(bf, "\177", 1))
	{
		if (*stp > 0)
		{
			(*stp)--;
			del_cap(msh, len);
		}
	}
}

int	shell_prompt(t_msh *msh, int len, int l, ssize_t stp)
{
	msh->line = NULL;
	tputs(save_cursor, 1, ft_putchar);
	msh->h_index = dbl_len(msh->history) - 1;
	while (!ft_strnstr(msh->buff, "\n", 1))
	{
		l = read(0, msh->buff, BUFF_SIZE);
		if (!ft_strncmp(msh->buff, "\e[A", 3)
			|| !ft_strncmp(msh->buff, "\e[B", 3))
			up_down(msh, msh->buff, &len, &stp);
		else if (!ft_strncmp(msh->buff, "\e[C", 3)
			|| !ft_strncmp(msh->buff, "\e[D", 3)
			|| !ft_strncmp(msh->buff, "\177", 1))
			right_left_del(msh, &stp, len, msh->buff);
		else if (!ft_strncmp(msh->buff, "\4", 1))
			{
				write(1, "exit\n", 5);
				exit(0);
			}
		else
			stp += write(1, msh->buff, l);
		if (ft_isprint(*msh->buff))
			make_line(&msh->line, *msh->buff);
		len = ft_strlen(msh->line);
	}
	*msh->buff = 0;
	return (1);
}
