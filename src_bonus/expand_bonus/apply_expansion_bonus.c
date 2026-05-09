/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_expansion_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:49 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "env_bonus/env_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static char	*append_str_bonus(char *t, char *s)
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

static char	*char_append_bonus(char *s, char c)
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

static char	*expand_one_bonus(t_shell *sh, const char *s, int *i)
{
	char	key[256];
	int		k;
	char	*val;

	*i = *i + 1;
	if (s[*i] == '?')
	{
		*i = *i + 1;
		return (tok_itoa_pos_bonus(sh->last_exit_status));
	}
	if (!is_name_start_bonus(s[*i]))
		return (ft_strdup("$"));
	k = 0;
	while (s[*i] && is_name_char_bonus(s[*i]) && k < 255)
		key[k++] = s[(*i)++];
	key[k] = '\0';
	val = env_get_bonus(sh, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

int	hd_process_line_bonus(t_shell *sh, t_redir *r, char *line, int fd)
{
	char	*new;

	new = line;
	if (r->heredoc_expand)
		new = apply_expansion_bonus(sh, line);
	if (!new)
		return (1);
	write(fd, new, ft_strlen(new));
	write(fd, "\n", 1);
	if (new != line)
		free(new);
	return (0);
}

char	*apply_expansion_bonus(t_shell *sh, char *line)
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
			e = expand_one_bonus(sh, line, &i);
			if (!e)
				return (free(t), NULL);
			t = append_str_bonus(t, e);
			continue ;
		}
		t = char_append_bonus(t, line[i++]);
	}
	if (!t)
		return (append_str_bonus(NULL, ""));
	return (t);
}
