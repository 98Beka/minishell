/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:02:12 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/28 11:43:11 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/libft/libft.h"
#include <sys/signal.h>

int		execute(t_msh *msh)
{
	if (!msh->cmd->arg[0])
		ft_putstr_fd("", 1);
	else if (!ft_strcmp(msh->cmd->arg[0], "env"))
		exec_env(msh);
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
	else
		return (launch(msh));
 	return (1);
}

int		loop(t_msh *msh)
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
	while(*msh->cmd->arg)
	{
		if(!execute(msh))
			return(0);
		if(msh->line)
			pars_line(msh ,&msh->line);
	}
	free(msh->line);
	return (1);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	t_msh	msh;
	
	msh.env = NULL;
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
