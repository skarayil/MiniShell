/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_continuation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:40 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "minishell_bonus.h"

static int	has_open_quote_bonus(const char *line)
{
	int	q;
	int	i;

	q = 0;
	i = 0;
	while (line[i])
	{
		if (q == 0 && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		i++;
	}
	return (q != 0);
}

static int	starts_with_pipe_bonus(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '|');
}

char	*join_continuation_bonus(t_shell *sh, char *line)
{
	char	*next;
	char	*tmp;

	while (has_open_quote_bonus(line)
		|| (isatty(STDIN_FILENO) && is_incomplete_bonus(sh, line)))
	{
		next = get_input_bonus("> ", STDIN_FILENO);
		if (!next)
			return (NULL);
		tmp = ft_strjoin(line, "\n");
		if (!tmp)
			return (NULL);
		line = ft_strjoin(tmp, next);
		if (!line)
			return (NULL);
		if (starts_with_pipe_bonus(next))
			return (line);
	}
	return (line);
}
