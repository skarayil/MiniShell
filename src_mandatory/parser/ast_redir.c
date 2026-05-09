/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2026/02/09 08:25:04 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser/parser.h"
#include "types.h"

static int	has_quotes(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static char	*strip_quotes(const char *s)
{
	char	*out;
	int		i;
	int		j;
	int		q;

	out = ft_gc_malloc(ft_strlen(s) + 1);
	if (!out)
		return (ft_strdup(s));
	i = 0;
	j = 0;
	q = 0;
	while (s[i])
	{
		if (q == 0 && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (s[i] == q)
			q = 0;
		else
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

static void	set_redir_file(t_redir *n, int type, char *file)
{
	if (type == R_HEREDOC && has_quotes(file))
	{
		n->file = strip_quotes(file);
		n->heredoc_expand = 0;
	}
	else if (type == R_HEREDOC)
	{
		n->file = ft_strdup(file);
		n->heredoc_expand = 1;
	}
	else
	{
		n->file = ft_strdup(file);
		n->heredoc_expand = 0;
	}
}

void	add_redir(t_ast *node, int type, char *file)
{
	t_redir	*n;
	t_redir	*it;

	n = ft_gc_malloc(sizeof(t_redir));
	if (!n)
		return ;
	n->type = type;
	n->next = NULL;
	n->heredoc_fd = -1;
	n->redir_fd = -1;
	set_redir_file(n, type, file);
	if (!node->redirs)
		node->redirs = n;
	else
	{
		it = node->redirs;
		while (it->next)
			it = it->next;
		it->next = n;
	}
}
