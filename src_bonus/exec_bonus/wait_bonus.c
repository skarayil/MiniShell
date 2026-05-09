/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:57 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_bonus/exec_bonus.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static int	process_node_heredocs_bonus(t_shell *sh, t_ast *node)
{
	t_redir	*r;
	int		ret;

	r = node->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			ret = run_heredoc_bonus(sh, r);
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

int	pre_process_heredocs_bonus(t_shell *sh, t_ast *node)
{
	if (!node)
		return (0);
	if (pre_process_heredocs_bonus(sh, node->left))
		return (1);
	if (pre_process_heredocs_bonus(sh, node->right))
		return (1);
	return (process_node_heredocs_bonus(sh, node));
}
