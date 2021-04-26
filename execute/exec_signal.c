/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:20:43 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/26 12:32:47 by hveiled          ###   ########.fr       */
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
	if (write(1, "\b\b  \b\b", 6) < 0)
		return ;
	return ;
}

//void	sigcat(int sig)
//{
//	(void)sig;
//	write(1, "\b\b\b\b", 6);
//	return ;
//}
