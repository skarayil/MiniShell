/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "expand_bonus/expand_bonus.h"
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

char	*handle_dollar_bonus(t_shell *sh, const char *s, int *i)
{
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (tok_itoa_pos_bonus(sh->last_exit_status));
	}
	if (s[*i] == '\0' || ft_strchr(" \t\n\"'", s[*i]))
		return (ft_strdup("$"));
	if (!is_name_start_bonus(s[*i]))
	{
		if (ft_isdigit(s[*i]))
			(*i)++;
		else
			return (ft_strdup("$"));
		return (ft_strdup(""));
	}
	return (exp_lookup_bonus(sh, s, i));
}

void	process_val_bonus(char ***res, char **buf, char *val, int q)
{
	int	j;

	j = 0;
	while (val[j])
	{
		if (q == 0 && (val[j] == ' ' || val[j] == '\t' || val[j] == '\n'))
		{
			if (*buf)
			{
				*res = exp_arr_add_bonus(*res, *buf);
				*buf = NULL;
			}
		}
		else
		{
			if (val[j] == '*' && q != 0)
				*buf = exp_char_append_bonus(*buf, QUOTE_MARKER);
			else
				*buf = exp_char_append_bonus(*buf, val[j]);
		}
		j++;
	}
}

char	**expand_token_bonus(t_shell *sh, char *raw)
{
	char	**res;
	char	*buf;
	char	**final;

	res = NULL;
	buf = NULL;
	exp_loop_bonus(sh, raw, &res, &buf);
	if (buf)
		res = exp_arr_add_bonus(res, buf);
	if (res == NULL && !buf && (ft_strchr(raw, '\'') || ft_strchr(raw, '"')))
		res = exp_arr_add_bonus(res, ft_strdup(""));
	final = expand_wildcards_bonus(res);
	if (!final)
		return (res);
	argv_free_bonus(res);
	return (final);
}
