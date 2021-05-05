/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:32:35 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/05 17:30:45 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static void	tcap_on(t_msh *msh)
{
	if (!ft_strcmp(msh->cmd->arg[0], "cat"))
	{
		msh->term.c_lflag |= ECHO;
		msh->term.c_lflag |= ICANON;
		tcsetattr(0, TCSANOW, &msh->term);
	}
}

static void	tcap_off(t_msh *msh)
{
	if (!ft_strcmp(msh->cmd->arg[0], "cat"))
	{
		msh->term.c_lflag &= ~(ECHO);
		msh->term.c_lflag &= ~(ICANON);
		tcsetattr(0, TCSANOW, &msh->term);
	}
}

static char	*change_notation(int i, unsigned long long inp, int sst)
{
	unsigned long long	tmp;
	char				*str;

	tmp = inp;
	if (!inp)
		return (ft_strdup("0"));
	while (tmp && i++ >= 0)
		tmp /= sst;
	str = malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	while (i-- >= 0)
	{
		if ((inp % sst) < 10)
			str[i] = (inp % sst) + 48;
		else
			str[i] = (inp % sst) + 87;
		inp /= sst;
	}
	return (str);
}

static int	excode_to_dec(int exit_code)
{
	int		code;
	char	*tmp;

	tmp = change_notation(0, exit_code /256, 10);
	code = ft_atoi(tmp);
	free(tmp);
	return (code);
}

int	exec_bin(t_msh *msh)
{
	pid_t	pid;
	char	*path;

	tcap_on(msh);
	pid = fork();
	if (pid < 0)
		return (ft_error(msh, NULL, NULL, 1));
	else if (pid == 0)
	{
		path = get_binary(msh, msh->cmd);
		if (msh->cmd->r_redir || msh->cmd->l_redir || msh->cmd->dbl_r_redir)
			if (!exec_redirect(msh, msh->cmd))
				return (0);
		if (execve(path, msh->cmd->arg, msh->env) < 0)
			exit(execve_error(msh, path, msh->cmd));
		free(path);
	}
	else
		if (waitpid(pid, &msh->code, 0) < 0)
			return (ft_error(msh, NULL, NULL, 1));
	msh->code = excode_to_dec(msh->code);
	tcap_off(msh);
	return (1);
}
