/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 02:39:33 by ehande            #+#    #+#             */
/*   Updated: 2021/04/28 12:30:19 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_end(char pf, char ch)
{
	return ((ch == ' ' && !(pf & DBL) && !(pf & SNGL))
		|| ch == ';' || ch == '|');
}

static char	get_flags(char ch, char **line)
{
	del_at_index(line, 0);
	return (ch);
}

static void	dollar(t_msh *msh, char **line)
{
	int		i;
	char	*d;
	char	*tmp;

	d = ft_strdup("");
	del_at_index(line, 0);
	while (line && **line && **line != ' ' && **line != '\"' && **line != '$')
		mkline_dlch(&d, line);
	if (*d == '?')
		tmp = ft_itoa(msh->code);
	else
		tmp = get_env_val(d, msh->env);
	if (!*d)
		tmp = ft_strdup("$");
	i = -1;
	if (!tmp)
		return ;
	while (tmp[++i])
		add_char_index(line, tmp[i], i);
	free(tmp);
	free(d);
}

static char	set_flags(char ch, t_msh *msh, char **line)
{
	if (ch == '\'' && msh->pf & SNGL)
		return (msh->pf = msh->pf & ~get_flags(SNGL, line));
	if (ch == '\"' && msh->pf & DBL)
		return (msh->pf = msh->pf & ~get_flags(DBL, line));
	if (ch == '\"' && !(msh->pf & SNGL))
		return (msh->pf = msh->pf | get_flags(DBL, line));
	if (ch == '\'' && !(msh->pf & DBL))
		return (msh->pf = msh->pf | get_flags(SNGL, line));
	if (ch == '\\' && !(msh->pf & SNGL))
		if (!(msh->pf & DBL) || ((msh->pf & DBL) && \
			((*line)[1] == '$' || (*line)[1] == '\\')))
			return (msh->pf = msh->pf | get_flags(SHL, line));
	return (ch);
}

char	*get_arg(t_msh *msh, char **line)
{
	char	*out;

	out = NULL;
	msh->pf = F_NONE;
	skip_sp(line);
	while (*line && **line && !is_end(msh->pf, **line))
	{
		set_flags(**line, msh, line);
		if (msh->pf & SHL)
		{
			mkline_dlch(&out, line);
			msh->pf = msh->pf & ~SHL;
		}
		if (msh->pf & SNGL)
			while (**line && **line != '\'' && !is_end(msh->pf, **line))
				mkline_dlch(&out, line);
		if (**line == '$')
			dollar(msh, line);
		if (**line && !(msh->pf & SNGL) && **line != '\"')
			mkline_dlch(&out, line);
	}
	return (out);
}
