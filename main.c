/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <hveiled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:02:12 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/04 09:20:38 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/ft_arr/ft_arr.h"
#include "utils/libft/libft.h"
#include <sys/signal.h>

int	execute(t_msh *msh)
{
	if (!msh->cmd->arg[0])
		return (write(1, "", 2));
	else if (!ft_strcmp(msh->cmd->arg[0], "env"))
		return (exec_env(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "pwd"))
		return (exec_pwd(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "exit"))
		return (exec_exit(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "cd"))
		return (exec_cd(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "export"))
		return (exec_export(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "unset"))
		return (exec_unset(msh));
	else if (!ft_strcmp(msh->cmd->arg[0], "echo"))
		return (exec_echo(msh));
	return (0);
}

int	loop(t_msh *msh)
{
	msh->line = NULL;
	ft_putstr_fd("minishell > ", 1);
	if (!shell_prompt(msh, 0, 0, 0))
		exec_exit(msh);
	if (!msh->line)
		msh->line = ft_strdup("");
	else
		set_history(msh);
	pars_line(msh, &msh->line);
	if (!set_fd(msh))
		return (1);
	while (*msh->cmd->arg)
	{
		if (!launch(msh))
			return (0);
		g_process_flag = 0;
		if (msh->line)
			pars_line(msh, &msh->line);
	}
	free(msh->cmd->arg);
	free(msh->cmd);
	free(msh->line);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void)ac;
	g_process_flag = 0;
	ft_bzero(&msh, sizeof(t_msh));
	init_history(&msh);
	get_envp(envp, &msh);
	set_env_val(&msh.env, ft_strdup("OLDPWD"), NULL);
	msh.shell_name = ft_strdup(av[0] + 2);
	set_termcap(&msh);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	while (loop(&msh))
		NULL;
	return (0);
}
