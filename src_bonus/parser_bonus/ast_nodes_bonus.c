/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:11:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

t_ast	*new_node_bonus(t_node_type type)
{
	t_ast	*n;

	n = ft_gc_malloc(sizeof(t_ast));
	if (!n)
		return (NULL);
	n->type = type;
	n->left = NULL;
	n->right = NULL;
	n->argv = NULL;
	n->redirs = NULL;
	return (n);
}

void	delete_ast_bonus(t_ast *node)
{
	(void)node;
}

int	tok_len_bonus(char **tok)
{
	int	i;

	i = 0;
	while (tok && tok[i])
		i++;
	return (i);
}

int	is_logic_bonus(char *s)
{
	return (ft_streq(s, "&&") || ft_streq(s, "||"));
}
