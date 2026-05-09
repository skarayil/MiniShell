/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:10:54 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

t_ast	*parse_pipeline_scope_bonus(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_op_bonus(tok, s, e, "|");
	if (idx == -1)
		return (parse_primary_bonus(tok, s, e));
	if (idx == s || idx == e - 1)
		return (syn_err_bonus("|"), NULL);
	if (idx > s && (ft_streq(tok[idx - 1], "<")
			|| ft_streq(tok[idx - 1], ">")
			|| ft_streq(tok[idx - 1], ">>")
			|| ft_streq(tok[idx - 1], "<<")
			|| ft_streq(tok[idx - 1], "<>")))
		return (syn_err_bonus("|"), NULL);
	node = new_node_bonus(NODE_PIPE);
	node->left = parse_pipeline_scope_bonus(tok, s, idx);
	if (!node->left)
		return (delete_ast_bonus(node), NULL);
	node->right = parse_primary_bonus(tok, idx + 1, e);
	if (!node->right)
		return (delete_ast_bonus(node), NULL);
	return (node);
}

t_ast	*parse_logic_scope_bonus(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_logic_op_bonus(tok, s, e);
	if (idx == -1)
		return (parse_pipeline_scope_bonus(tok, s, e));
	if (idx == s || idx == e - 1)
		return (syn_err_bonus(tok[idx]), NULL);
	if (ft_streq(tok[idx], "&&"))
		node = new_node_bonus(NODE_AND);
	else
		node = new_node_bonus(NODE_OR);
	node->left = parse_logic_scope_bonus(tok, s, idx);
	if (!node->left)
		return (delete_ast_bonus(node), NULL);
	node->right = parse_pipeline_scope_bonus(tok, idx + 1, e);
	if (!node->right)
		return (delete_ast_bonus(node), NULL);
	return (node);
}

static t_ast	*parse_bg_right_bonus(t_ast *node, char **tok, int idx, int e)
{
	if (idx + 1 < e)
	{
		node->right = parse_logic_scope_bonus(tok, idx + 1, e);
		if (!node->right)
			return (delete_ast_bonus(node), NULL);
	}
	return (node);
}

t_ast	*parse_list_scope_bonus(char **tok, int s, int e)
{
	int		idx;
	t_ast	*node;

	idx = find_op_bonus(tok, s, e, "&");
	if (idx == -1)
		return (parse_logic_scope_bonus(tok, s, e));
	if (idx == s)
		return (syn_err_bonus("&"), NULL);
	node = new_node_bonus(NODE_BG);
	node->left = parse_list_scope_bonus(tok, s, idx);
	if (!node->left)
		return (delete_ast_bonus(node), NULL);
	return (parse_bg_right_bonus(node, tok, idx, e));
}
