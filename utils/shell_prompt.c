/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:48:05 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/18 05:59:56 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void up_down(t_msh *msh, char *bf, int *len, ssize_t *stp)
{
	char *tmp;
	
	clean_console(msh, len);
		tputs(restore_cursor, 1, ft_putchar);
	if (!ft_strncmp(bf, "\e[A", 3))
	{
		if (msh->h_index)
			msh->h_index -=1;
			tmp =  msh->history[msh->h_index];
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

void right_left_del(t_msh *msh, ssize_t *stp, int len, char *bf)
{
	if (!ft_strncmp(bf, "\e[C", 3))
	 	if (*stp < len)
		{
			(*stp)++;
			tputs(cursor_right, 1, ft_putchar);
		}
	if (!ft_strncmp(bf, "\e[D", 3))
		if (*stp > 0)
		{
			(*stp)--;
			tputs(cursor_left, 1, ft_putchar);
		}
	if (!ft_strncmp(bf, "\177", 1))
		if (*stp > 0)
		{
			(*stp)--;
			del_cap(msh, len);
		}
}

int	shell_prompt(t_msh *msh, char *bf, int len, int l, ssize_t stp)
{
	msh->line = NULL;
	tputs(save_cursor, 1, ft_putchar);
	msh->h_index = dbl_len(msh->history) - 1;
	while (!ft_strnstr(bf, "\n", 1))
	{
		l = read(0, msh->buff, BUFF_SIZE);
		if (!ft_strncmp(bf, "\e[A", 3) || !ft_strncmp(bf, "\e[B", 3))
			up_down(msh, bf, &len, &stp);
		else if (!ft_strncmp(bf, "\e[C", 3) ||\
		 !ft_strncmp(bf, "\e[D", 3) || !ft_strncmp(bf, "\177", 1))
			right_left_del(msh, &stp, len, bf);
		else if (!ft_strncmp(bf, "\4", 1))
			return (0);
		else
			stp += write(1, bf, l);
		if (ft_isprint(*bf))
			make_line(&msh->line, *bf);
		len = ft_strlen(msh->line);
	}
	*bf = 0;
	return (1);
}
