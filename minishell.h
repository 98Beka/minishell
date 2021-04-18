/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:07:09 by hveiled           #+#    #+#             */
/*   Updated: 2021/04/18 04:23:56 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "./utils/libft/libft.h"
# include "./utils/gnl/get_next_line.h"
# include "./utils/ft_arr/ft_arr.h"
# include <signal.h>
# include <term.h>

# define BUFF_SIZE 4096
# define CMD	0b10000000
# define CD		0b01000000
# define EXIT	0b00000001

//flags of parser
# define F_NONE 0b00000000
# define SNGL   0b10000000
# define DBL    0b01000000
# define SHL    0b00100000

typedef struct s_cmd
{
	int				pipe;
	int				r_redir;
	int				l_redir;
	char			*file;
	char			**arg;
	struct s_cmd	*next;
}t_cmd;				

typedef struct s_msh
{
	int				fd;
	int				pipefd[2];
	int				num_redir;
	char			*line;
	char			*shell_name;
	char			*term_name;
	char			**env;
	char			**history;
	int				h_index;
	t_cmd			*cmd;
	char			pf;
	char			cmd_flag;
	char			buff[BUFF_SIZE];
	struct termios	term;
}t_msh;

int		pars_line(t_msh *msh, char **line);
int		get_envp(char **envp, t_msh *msh);
void	sort_envp(char ***env);
char	*get_env_val(char *key, char **env);
int		set_env_val(char ***env, char *key, char *value);
int		del_env_val(char ***env, char *key);
void	clear(char **array);
void	exec_env(char **env);
int		exec_pwd(t_msh *msh);
int		exec_exit(t_msh *msh);
int		exec_cd(t_msh *msh);
int		exec_export(t_msh *msh);
int		exec_unset(t_msh *msh);
int		exec_echo(t_msh *msh);

int		ft_error(t_msh *msh, char *msg);
int		set_termcap(t_msh *msh);
int		shell_prompt(t_msh *msh, char *bf, int len, int l, ssize_t stp);
int		exec_bin(t_msh *msh);
char	*get_binary(t_msh *msh);
int		exec_pipe(t_msh *msh);
int		launch(t_msh *msh);
int		exec_child(t_msh *msh, char *path);
void	skip_sp(char **line);
void	skip_sp_ch(char **line, char ch);
void	new_cmd(t_msh *msh, t_cmd **cmd, char **line);
t_cmd	*last_cmd(t_cmd *cmd);
char	*get_arg(t_msh *msh, char **line);
void    mkline_dlch(char **out, char **line);
void	change_cmd_line(t_msh *msh);
void 	del_cap(t_msh *msh, int len);
void 	clean_console(t_msh *msh, int *len);
void	set_history(t_msh *msh);
void	init_history(t_msh *msh);

#endif // !MINISHELL_H
