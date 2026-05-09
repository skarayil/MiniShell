/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:04:31 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "types.h"

static int	exec_seq(t_shell *sh, t_ast *node)
{
	int	ret;

	ret = exec_ast(sh, node->left);
	if (node->right)
		ret = exec_ast(sh, node->right);
	return (ret);
}

int	exec_ast(t_shell *sh, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (exec_pipe(sh, node));
	if (node->type == NODE_SEQ)
		return (exec_seq(sh, node));
	return (exec_cmd(sh, node));
}
