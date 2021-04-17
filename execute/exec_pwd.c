/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:47:14 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/14 11:48:23 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pwd(t_msh *msh)
{
	char	buff[BUFF_SIZE];

	(void)msh;
	if (!(getcwd(buff, BUFF_SIZE)))
		ft_error(msh, NULL);
	ft_putendl_fd(buff, 1);
	return (1);
}
