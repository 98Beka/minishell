/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehande <ehande@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:08:42 by hveiled           #+#    #+#             */
/*   Updated: 2021/05/06 16:55:26 by ehande           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_arg_dop(t_msh *msh, char *out)
{
	write(1, "> ", 2);
	shell_prompt(msh, 0, 0, 0);
	return (out);
}

int	is_end(char pf, char ch)
{
	return (((ch == ' ' || ch == ';' || ch == '|'
	|| ch == '<' || ch == '>') \
	&& !(pf & DBL) && !(pf & SNGL)));
}

char	get_flags(char ch, char **line)
{
	del_at_index(line, 0);
	return (ch);
}