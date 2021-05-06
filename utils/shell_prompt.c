/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:48:05 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 21:58:36 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_arr/ft_arr.h"
#include "libft/libft.h"
#include <term.h>

void	up_down(t_msh *msh, char *bf, int *len, ssize_t *stp)
{
	char	*tmp;

	tmp = NULL;
	clean_console(msh, len);
	if (!*msh->history)
		return ;
	tputs(restore_cursor, 1, ft_putchar);
	if (!ft_strncmp(bf, "\e[A", 3) && msh->h_index > 0)
		msh->h_index -=1;
	else if (!ft_strncmp(bf, "\e[B", 3) && msh->history[msh->h_index + 1])
		msh->h_index +=1;
	tmp = msh->history[msh->h_index];
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

void	exec_sigquit(t_msh *msh)
{
	char	*var;

	var = get_env_val("SHLVL", msh->env);
	tputs(restore_cursor, 1, ft_putchar);
	write(1, "exit\n", 5);
	if (!ft_strcmp(var, "2"))
	{
		msh->term.c_lflag |= ECHO;
		msh->term.c_lflag |= ICANON;
		tcsetattr(0, TCSANOW, &msh->term);
	}
	free(var);
	exit(0);
}

int	shell_prompt(t_msh *msh, int len, int l, ssize_t stp)
{
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
		else if (!ft_strncmp(msh->buff, "\034", 1))
			continue ;
		else if (!ft_strncmp(msh->buff, "\4", 1) && !stp)
			exec_sigquit(msh);
		else
			stp += write(1, msh->buff, l);
		if (ft_isprint(*msh->buff))
			make_line(&msh->line, *msh->buff);
		len = ft_strlen(msh->line);
	}
	*msh->buff = 0;
	return (1);
}
