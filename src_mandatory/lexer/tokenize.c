/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer/lexer.h"
#include "libft.h"
#include "types.h"

static char	**tok_process(char **v, int *n, char *t)
{
	char	**new_v;

	if (!t)
	{
		tok_free_all(v);
		return (NULL);
	}
	new_v = tok_push(v, *n, t);
	if (!new_v)
	{
		tok_free_all(v);
		return (NULL);
	}
	(*n)++;
	return (new_v);
}

static char	*read_op_tail(char c, char nxt, int *i)
{
	if (c == '>' && nxt == '|')
	{
		*i = *i + 1;
		return (ft_strdup(">"));
	}
	if (c == '<' && nxt == '>')
	{
		*i = *i + 1;
		return (ft_strdup("<>"));
	}
	return (read_single_op(c));
}

static char	*read_op(const char *l, int *i)
{
	char	c;
	char	nxt;

	c = l[*i];
	nxt = l[*i + 1];
	*i = *i + 1;
	if (c == '<' && nxt == '<')
		return (read_double_op(c, i));
	if (c == '>' && nxt == '>')
		return (read_double_op(c, i));
	return (read_op_tail(c, nxt, i));
}

static char	*get_token(const char *line, int *i)
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
	if (is_op(line[*i]))
		return (read_op(line, i));
	return (read_word(line, i));
}

char	**tokenize(t_shell *sh, const char *line)
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
		skip_ws(line, &i);
		if (!line[i])
			break ;
		t = get_token(line, &i);
		v = tok_process(v, &n, t);
		if (!v)
			return (NULL);
	}
	return (v);
}
