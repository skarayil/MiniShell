/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:15:51 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "libft.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

static int	is_limiter_bonus(const char *line, const char *lim)
{
	size_t	ll;

	if (!line || !lim)
		return (0);
	ll = ft_strlen(lim);
	if (ft_strncmp(line, lim, ll) != 0)
		return (0);
	if (line[ll] != '\0')
		return (0);
	return (1);
}

static char	*grow_buf_bonus(char *buf, size_t *cap)
{
	char	*new;
	size_t	i;

	*cap *= 2;
	new = malloc(*cap);
	if (!new)
		return (free(buf), NULL);
	i = 0;
	while (buf[i])
	{
		new[i] = buf[i];
		i++;
	}
	new[i] = '\0';
	free(buf);
	return (new);
}

static char	*read_stdin_line_bonus(void)
{
	char	*buf;
	size_t	cap;
	size_t	len;
	char	c;

	cap = 256;
	len = 0;
	buf = malloc(cap);
	if (!buf)
		return (NULL);
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (c == '\n')
			break ;
		if (len + 1 >= cap)
			buf = grow_buf_bonus(buf, &cap);
		if (!buf)
			return (NULL);
		buf[len++] = c;
	}
	if (len == 0 && c != '\n')
		return (free(buf), NULL);
	buf[len] = '\0';
	return (buf);
}

static int	hd_read_line_bonus(char **line)
{
	if (isatty(STDIN_FILENO))
		*line = readline("heredoc> ");
	else
		*line = read_stdin_line_bonus();
	if (!*line)
		return (0);
	return (1);
}

int	hd_loop_bonus(t_shell *sh, t_redir *r, int fd)
{
	char	*line;

	(void)sh;
	while (1)
	{
		if (!hd_read_line_bonus(&line))
		{
			if (g_sig.sig == SIGINT)
				return (130);
			write(2,
				"minishell: warning: here-document delimited by EOF\n", 51);
			break ;
		}
		if (g_sig.sig == SIGINT)
			return (free(line), 130);
		if (is_limiter_bonus(line, r->file))
			return (free(line), 0);
		if (hd_process_line_bonus(sh, r, line, fd) != 0)
			return (1);
		free(line);
	}
	return (0);
}
