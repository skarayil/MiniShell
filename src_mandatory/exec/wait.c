/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:06:26 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "parser/parser.h"
#include "types.h"

static int	process_node_heredocs(t_shell *sh, t_ast *node)
{
	t_redir	*r;
	int		ret;

	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			ret = run_heredoc(sh, r);
			if (ret != 0)
			{
				sh->last_exit_status = ret;
				return (1);
			}
		}
		r = r->next;
	}
	return (0);
}

int	pre_process_heredocs(t_shell *sh, t_ast *node)
{
	if (!node)
		return (0);
	if (pre_process_heredocs(sh, node->left))
		return (1);
	if (pre_process_heredocs(sh, node->right))
		return (1);
	return (process_node_heredocs(sh, node));
}
