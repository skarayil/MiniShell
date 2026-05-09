/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:44 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static char	**tok_process_bonus(char **v, int *n, char *t)
{
	char	**new_v;

	if (!t)
	{
		tok_free_all_bonus(v);
		return (NULL);
	}
	new_v = tok_push_bonus(v, *n, t);
	if (!new_v)
	{
		tok_free_all_bonus(v);
		return (NULL);
	}
	(*n)++;
	return (new_v);
}

static char	*read_op_tail_bonus(char c, char nxt, int *i)
{
	if (c == '<' && nxt == '>')
	{
		*i = *i + 1;
		return (ft_strdup("<>"));
	}
	if (c == '>' && nxt == '|')
	{
		*i = *i + 1;
		return (ft_strdup(">"));
	}
	return (read_single_op_bonus(c));
}

static char	*read_op_bonus(const char *l, int *i)
{
	char	c;
	char	nxt;

	c = l[*i];
	nxt = l[*i + 1];
	*i = *i + 1;
	if (c == '|' && nxt == '|')
		return (read_double_op_bonus(c, i));
	if (c == '&' && nxt == '&')
		return (read_double_op_bonus(c, i));
	if (c == '<' && nxt == '<' && l[*i + 1] == '<')
	{
		*i = *i + 2;
		return (ft_strdup("<<<"));
	}
	if (c == '<' && nxt == '<')
		return (read_double_op_bonus(c, i));
	if (c == '>' && nxt == '>')
		return (read_double_op_bonus(c, i));
	return (read_op_tail_bonus(c, nxt, i));
}

static char	*get_token_bonus(const char *line, int *i)
{
	char	buf[3];

	if (line[*i] >= '0' && line[*i] <= '2'
		&& (line[*i + 1] == '>' || line[*i + 1] == '<'))
	{
		buf[0] = '\x02';
		buf[1] = line[*i];
		buf[2] = '\0';
		*i = *i + 1;
		return (ft_strdup(buf));
	}
	if (is_op_bonus(line[*i]))
		return (read_op_bonus(line, i));
	return (read_word_bonus(line, i));
}

char	**tokenize_bonus(t_shell *sh, const char *line)
{
	char	**v;
	char	*t;
	int		i;
	int		n;

	(void)sh;
	v = NULL;
	i = 0;
	n = 0;
	while (line[i])
	{
		skip_ws_bonus(line, &i);
		if (!line[i])
			break ;
		t = get_token_bonus(line, &i);
		v = tok_process_bonus(v, &n, t);
		if (!v)
			return (NULL);
	}
	return (v);
}
