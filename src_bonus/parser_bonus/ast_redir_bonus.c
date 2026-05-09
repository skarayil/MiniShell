/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:30 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static int	has_quotes_bonus(const char *s)
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

static char	*strip_quotes_bonus(const char *s)
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

static void	set_redir_file_bonus(t_redir *n, int type, char *file)
{
	if (type == R_HEREDOC && has_quotes_bonus(file))
	{
		n->file = strip_quotes_bonus(file);
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

void	add_redir_bonus(t_ast *node, int type, char *file)
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
	set_redir_file_bonus(n, type, file);
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
