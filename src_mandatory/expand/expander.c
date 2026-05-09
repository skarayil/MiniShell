/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:09:59 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "expand/expand.h"
#include "lexer/lexer.h"
#include "libft.h"
#include "types.h"

char	*handle_dollar(t_shell *sh, const char *s, int *i)
{
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (tok_itoa_pos(sh->last_exit_status));
	}
	if (s[*i] == '\0' || ft_strchr(" \t\n\"'", s[*i]))
		return (ft_strdup("$"));
	if (!is_name_start(s[*i]))
	{
		if (ft_isdigit(s[*i]))
			(*i)++;
		else
			return (ft_strdup("$"));
		return (ft_strdup(""));
	}
	return (exp_lookup(sh, s, i));
}

void	process_val(char ***res, char **buf, char *val, int q)
{
	int	j;

	j = 0;
	while (val[j])
	{
		if (q == 0 && (val[j] == ' ' || val[j] == '\t' || val[j] == '\n'))
		{
			if (*buf)
			{
				*res = exp_arr_add(*res, *buf);
				*buf = NULL;
			}
		}
		else
			*buf = exp_char_append(*buf, val[j]);
		j++;
	}
}

char	**expand_token(t_shell *sh, char *raw)
{
	char	**res;
	char	*buf;

	res = NULL;
	buf = NULL;
	exp_loop(sh, raw, &res, &buf);
	if (buf)
		res = exp_arr_add(res, buf);
	if (res == NULL && !buf && (ft_strchr(raw, '\'') || ft_strchr(raw, '"')))
		res = exp_arr_add(res, ft_strdup(""));
	return (res);
}
