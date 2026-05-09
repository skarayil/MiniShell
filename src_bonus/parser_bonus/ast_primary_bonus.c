/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_primary_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:13 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static int	sub_redirs_bonus(t_ast *node, char **tok, int last, int e)
{
	int	i;

	i = last + 1;
	while (i < e)
	{
		if (ft_streq(tok[i], "<") || ft_streq(tok[i], ">") || ft_streq(tok[i],
				">>") || ft_streq(tok[i], "<<") || ft_streq(tok[i], "<>"))
		{
			if (handle_redir_bonus(node, tok, &i, e))
				return (1);
		}
		else
			return (syn_err_bonus(tok[i]));
		i++;
	}
	return (0);
}

t_ast	*parse_subshell_bonus(char **tok, int s, int e)
{
	int		last;
	t_ast	*node;

	last = find_matching_paren_bonus(tok, s, e);
	if (last == -1)
		return (parse_simple_bonus(tok, s, e));
	node = new_node_bonus(NODE_SUBSHELL);
	if (s + 1 == last)
		return (syn_err_bonus(")"), delete_ast_bonus(node), NULL);
	node->left = parse_logic_scope_bonus(tok, s + 1, last);
	if (!node->left)
		return (delete_ast_bonus(node), NULL);
	if (sub_redirs_bonus(node, tok, last, e))
		return (delete_ast_bonus(node), NULL);
	return (node);
}

t_ast	*parse_primary_bonus(char **tok, int s, int e)
{
	if (s >= e)
		return (NULL);
	if (ft_streq(tok[s], "("))
		return (parse_subshell_bonus(tok, s, e));
	return (parse_simple_bonus(tok, s, e));
}
