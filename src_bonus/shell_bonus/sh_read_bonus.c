/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:13:23 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell_bonus.h"
#include "signals_bonus/signals_bonus.h"

static char	*read_line_fd_bonus(int fd)
{
	char	*line;
	char	buf[2];
	int		r;

	line = NULL;
	buf[1] = '\0';
	while (1)
	{
		r = read(fd, buf, 1);
		if (r <= 0)
			break ;
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, buf);
		if (buf[0] == '\n')
			return (ft_substr(line, 0, ft_strlen(line) - 1));
	}
	return (line);
}

static int	sig_event_hook_bonus(void)
{
	if (g_sig.sig == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

char	*get_input_bonus(const char *prompt, int fd)
{
	char	*raw;
	char	*gc;

	if (isatty(STDIN_FILENO))
	{
		rl_event_hook = sig_event_hook_bonus;
		raw = readline(prompt);
		if (!raw || g_sig.sig == SIGINT)
		{
			free(raw);
			return (NULL);
		}
		gc = ft_strdup(raw);
		free(raw);
		return (gc);
	}
	return (read_line_fd_bonus(fd));
}
