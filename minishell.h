/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:07:09 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 16:20:44 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <term.h>
# include "./utils/libft/libft.h"
# include "./utils/gnl/get_next_line.h"
# include "./utils/ft_arr/ft_arr.h"
# include <sys/_types/_pid_t.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

# define BUFF_SIZE 4096
# define CMD	0b10000000
# define CD		0b01000000
# define EXIT	0b00000001

# define F_NONE 0b00000000
# define SNGL   0b10000000
# define DBL    0b01000000
# define SHL    0b00100000

typedef struct s_cmd
{
	int				pipe;
	int				r_redir;
	int				dbl_r_redir;
	int				l_redir;
	char			*file;
	char			**arg;
	struct s_cmd	*next;
}t_cmd;				

typedef struct s_msh
{
	int				fd;
	int				**pfd;
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
	int				cmd_count;
	int				pipe_count;
	char			*path;
	DIR				*dir;
	int				code;
	struct termios	term;
}t_msh;

int		g_process_flag;
int		g_status;
int		pars_line(t_msh *msh, char **line);
int		get_envp(char **envp, t_msh *msh);
void	sort_envp(char ***env);
char	*get_env_val(char *key, char **env);
int		set_env_val(char ***env, char *key, char *value);
int		del_env_val(char ***env, char *key);
void	clear(char **array);
int		exec_env(t_msh *msh);
int		exec_pwd(t_msh *msh);
int		exec_exit(t_msh *msh);
int		exec_cd(t_msh *msh);
int		exec_export(t_msh *msh);
int		exec_unset(t_msh *msh);
int		exec_echo(t_msh *msh);
int		exec_redirect(t_msh *msh, t_cmd *cmnd);
int		exec_piped_cmd(t_msh *msh, t_cmd *cmnd, pid_t *pid);
int		exec_single_cmd(t_msh *msh);
int		exec_bin(t_msh *msh);
int		execute(t_msh *msh);
int		execve_error(t_msh *msh, char *path, t_cmd *cmnd);
int		set_fd(t_msh *msh);
void	set_pfd(t_msh *msh, int i, int cmd);
void	sigint(int sn);
void	sigquit(int sn);
void	sigcat(int sn);
int		ft_error(t_msh *msh, char *msg, t_cmd *cmd_name, int exit_code);
int		set_termcap(t_msh *msh);
int		shell_prompt(t_msh *msh, int len, int l, ssize_t stp);
char	*get_binary(t_msh *msh, t_cmd *cmd);
int		launch(t_msh *msh);
int		exec_child(t_msh *msh);
int		exec_parent(t_msh *msh, char *bin_path);
void	skip_sp(char **line);
void	skip_sp_ch(char **line, char ch);
void	new_cmd(t_cmd **cmd);
t_cmd	*last_cmd(t_cmd *cmd);
void	mkline_dlch(char **out, char **line);
void	change_cmd_line(t_msh *msh);
void	del_cap(t_msh *msh, int len);
void	clean_console(t_msh *msh, int *len);
void	set_history(t_msh *msh);
void	init_history(t_msh *msh);
void	free_msh(t_msh *msh, pid_t *pid);
char	*get_arg_dop(t_msh *msh, char *out);
char	*get_arg(t_msh *msh, char **line, char *out);
char	get_flags(char ch, char **line);
int		is_end(char pf, char ch);
#endif
