/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:07:17 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/10 20:46:52 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "env/env.h"
#include "expand/expand.h"
#include "lexer/lexer.h"
#include "libft.h"
#include "types.h"

static char	*append_str(char *t, char *s)
{
	char	*out;
	size_t	lt;
	size_t	ls;

	if (!s)
		return (t);
	lt = 0;
	if (t)
		lt = ft_strlen(t);
	ls = ft_strlen(s);
	out = malloc(lt + ls + 1);
	if (!out)
		return (free(t), NULL);
	if (t)
		ft_memcpy(out, t, lt);
	ft_memcpy(out + lt, s, ls);
	out[lt + ls] = '\0';
	free(t);
	return (out);
}

static char	*char_append(char *s, char c)
{
	char	*out;
	size_t	l;

	l = 0;
	if (s)
		l = ft_strlen(s);
	out = malloc(l + 2);
	if (!out)
		return (free(s), NULL);
	if (s)
		ft_memcpy(out, s, l);
	out[l] = c;
	out[l + 1] = '\0';
	free(s);
	return (out);
}

static char	*expand_one(t_shell *sh, const char *s, int *i)
{
	char	key[256];
	int		k;
	char	*val;

	*i = *i + 1;
	if (s[*i] == '?')
	{
		*i = *i + 1;
		return (tok_itoa_pos(sh->last_exit_status));
	}
	if (!is_name_start(s[*i]))
		return (ft_strdup("$"));
	k = 0;
	while (s[*i] && is_name_char(s[*i]) && k < 255)
		key[k++] = s[(*i)++];
	key[k] = '\0';
	val = env_get(sh, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

int	hd_process_line(t_shell *sh, t_redir *r, char *line, int fd)
{
	char	*new;

	new = line;
	if (r->heredoc_expand)
		new = apply_expansion(sh, line);
	if (!new)
		return (1);
	write(fd, new, ft_strlen(new));
	write(fd, "\n", 1);
	if (new != line)
		free(new);
	return (0);
}

char	*apply_expansion(t_shell *sh, char *line)
{
	char	*t;
	char	*e;
	int		i;

	t = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			e = expand_one(sh, line, &i);
			if (!e)
				return (free(t), NULL);
			t = append_str(t, e);
			continue ;
		}
		t = char_append(t, line[i++]);
	}
	if (!t)
		return (append_str(NULL, ""));
	return (t);
}
