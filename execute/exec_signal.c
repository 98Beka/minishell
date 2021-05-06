/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:20:43 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 22:06:06 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) < 0)
		return ;
	if (!g_process_flag)
		write(1, "minishell > ", 12);
	tputs(save_cursor, 1, ft_putchar);
	signal(SIGINT, sigint);
}

void	sigquit(int sig)
{
	(void)sig;
	if (g_process_flag)
		write(1, "Quit: 3\n", 8);
	g_process_flag = 0;
}
