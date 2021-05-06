/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 02:39:33 by ehande            #+#    #+#             */
/*   Updated: 2021/05/06 19:10:34 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dollar(t_msh *msh, char **line)
{
	int		i;
	char	*d;
	char	*tmp;

	d = ft_strdup("");
	del_at_index(line, 0);
	while (line && **line && ft_isalnum(**line))
		mkline_dlch(&d, line);
	if (*d == '?')
		tmp = ft_itoa(msh->code);
	else
		tmp = get_env_val(d, msh->env);
	if (!*d)
		tmp = ft_strdup("$");
	i = -1;
	free(d);
	if (!tmp)
		return ;
	while (tmp[++i])
		add_char_index(line, tmp[i], i);
	free(tmp);
	
}

static char	set_flags(char ch, t_msh *msh)
{
	if (ch == '\'' && msh->pf & SNGL)
		return (msh->pf = msh->pf & ~get_flags(SNGL, &msh->line));
	if (ch == '\"' && msh->pf & DBL)
		return (msh->pf = msh->pf & ~get_flags(DBL, &msh->line));
	if (ch == '\"' && !(msh->pf & SNGL))
		return (msh->pf = msh->pf | get_flags(DBL, &msh->line));
	if (ch == '\'' && !(msh->pf & DBL))
		return (msh->pf = msh->pf | get_flags(SNGL, &msh->line));
	if (ch == '\\' && !(msh->pf & SNGL))
		if (!(msh->pf & DBL) || ((msh->pf & DBL) && \
			((msh->line[1] == '$' || msh->line[1] == '\\'))))
			return (msh->pf = msh->pf | get_flags(SHL, &msh->line));
	return (ch);
}

char	*get_arg(t_msh *msh, char *out, char pf)
{
	msh->pf = pf;
	skip_sp(&msh->line);
	while (msh->line[0] && !is_end(msh->pf, *msh->line))
	{
		set_flags(*msh->line, msh);
		if (check_flags(msh->pf) && close_input(msh))
			get_arg_dop(msh, *out);
		if (msh->pf & SHL)
		{
			mkline_dlch(&out, &msh->line);
			msh->pf = msh->pf & ~SHL;
		}
		if (msh->pf & SNGL)
		{
			while (msh->line && *msh->line != '\'' && !is_end(msh->pf, *msh->line))
				mkline_dlch(&out, &msh->line);
			del_at_index(&msh->line, 0);
		}
		if (*msh->line == '$')
			dollar(msh, &msh->line);
		set_flags(*msh->line, msh);
		if (msh->line[0] && *msh->line != '\"' && !is_end(msh->pf, *msh->line))
			mkline_dlch(&out, &msh->line);
	}
	return (out);
}
