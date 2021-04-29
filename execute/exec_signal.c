/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:20:43 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/30 02:17:56 by hveiled          ###   ########.fr       */
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
	if (g_process_flag)
		write(1, "Quit: 3\n", 8);
	g_process_flag = 0;
}
