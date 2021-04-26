/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:51:37 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/26 17:51:21 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/termios.h>

int	set_termcap(t_msh *msh)
{
	char			*term_name;

	msh->line = NULL;
	term_name = "xterm-256color";
	tcgetattr(0, &msh->term);
	//msh->term.c_lflag &= ~(ISIG);
	msh->term.c_lflag &= ~(ECHO);
	msh->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &msh->term);
	tgetent(0, term_name);
	return (1);
}
