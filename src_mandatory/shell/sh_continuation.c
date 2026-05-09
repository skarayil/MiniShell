/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_continuation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:36 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static int	has_open_quote(const char *line)
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

static int	is_trailing_pipe(const char *line)
{
	int	i;
	int	q;
	int	found_word;

	q = 0;
	found_word = 0;
	i = 0;
	while (line[i])
	{
		if (q == 0 && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		else if (!q && line[i] != ' ' && line[i] != '\t' && line[i] != '|')
			found_word = 1;
		i++;
	}
	if (q || !found_word)
		return (0);
	i = (int)ft_strlen(line) - 1;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
		i--;
	return (i >= 0 && line[i] == '|');
}

static int	starts_with_pipe(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '|');
}

char	*join_continuation(char *line)
{
	char	*next;
	char	*tmp;

	while (has_open_quote(line)
		|| (isatty(STDIN_FILENO) && is_trailing_pipe(line)))
	{
		next = get_input("> ", STDIN_FILENO);
		if (!next)
			return (NULL);
		tmp = ft_strjoin(line, "\n");
		if (!tmp)
			return (NULL);
		line = ft_strjoin(tmp, next);
		if (!line)
			return (NULL);
		if (starts_with_pipe(next))
			return (line);
	}
	return (line);
}
