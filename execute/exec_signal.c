/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:20:43 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/30 02:05:26 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint(int sig)
{
	(void)sig;
	if (write(1, "\b  \n", 5) < 0)
		return ;
	write(1, "minishell > ", 13);
	signal(SIGINT, sigint);
}

void	sigquit(int sig)
{
	(void)sig;
	if (process_flag)
		write(1, "Quit: 3\n", 8);
	process_flag = 0;
}

//void	sigcat(int sig)
//{
//	(void)sig;
//	write(1, "\b\b\b\b", 6);
//	return ;
//}
