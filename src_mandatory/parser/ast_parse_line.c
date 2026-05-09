/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/09 09:02:43 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "parser/parser.h"
#include "types.h"

static t_ast	*parse_seq_scope(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_op(tok, s, e, ";");
	if (idx == -1)
		return (parse_pipeline_scope(tok, s, e));
	if (idx == s)
		return (syn_err(";"), NULL);
	node = new_node(NODE_SEQ);
	node->left = parse_seq_scope(tok, s, idx);
	if (!node->left)
		return (delete_ast(node), NULL);
	if (idx + 1 < e)
	{
		node->right = parse_pipeline_scope(tok, idx + 1, e);
		if (!node->right)
			return (delete_ast(node), NULL);
	}
	return (node);
}

t_ast	*parse_line(char **toks)
{
	int	len;

	len = tok_len(toks);
	if (len == 0)
		return (NULL);
	return (parse_seq_scope(toks, 0, len));
}
