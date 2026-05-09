/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:11:53 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static t_ast	*parse_seq_scope_bonus(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_op_bonus(tok, s, e, ";");
	if (idx == -1)
		return (parse_list_scope_bonus(tok, s, e));
	if (idx == s)
		return (syn_err_bonus(";"), NULL);
	node = new_node_bonus(NODE_SEQ);
	node->left = parse_seq_scope_bonus(tok, s, idx);
	if (!node->left)
		return (delete_ast_bonus(node), NULL);
	if (idx + 1 < e)
	{
		node->right = parse_list_scope_bonus(tok, idx + 1, e);
		if (!node->right)
			return (delete_ast_bonus(node), NULL);
	}
	return (node);
}

t_ast	*parse_line_bonus(char **toks)
{
	int	len;

	len = tok_len_bonus(toks);
	if (len == 0)
		return (NULL);
	return (parse_seq_scope_bonus(toks, 0, len));
}
