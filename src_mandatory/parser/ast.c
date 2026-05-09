/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2026/02/09 09:05:39 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser/parser.h"
#include "types.h"

t_ast	*parse_pipeline_scope(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_op(tok, s, e, "|");
	if (idx == -1)
		return (parse_primary(tok, s, e));
	if (idx == s || idx == e - 1)
		return (syn_err("|"), NULL);
	if (idx > s && (ft_streq(tok[idx - 1], "<")
			|| ft_streq(tok[idx - 1], ">")
			|| ft_streq(tok[idx - 1], ">>")
			|| ft_streq(tok[idx - 1], "<<")))
		return (syn_err("|"), NULL);
	node = new_node(NODE_PIPE);
	node->left = parse_pipeline_scope(tok, s, idx);
	if (!node->left)
		return (delete_ast(node), NULL);
	node->right = parse_primary(tok, idx + 1, e);
	if (!node->right)
		return (delete_ast(node), NULL);
	return (node);
}
