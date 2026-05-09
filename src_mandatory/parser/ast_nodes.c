/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                  :+:      :+:    :+:   */
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

t_ast	*new_node(t_node_type type)
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

void	delete_ast(t_ast *node)
{
	(void)node;
}

int	tok_len(char **tok)
{
	int	i;

	i = 0;
	while (tok && tok[i])
		i++;
	return (i);
}
