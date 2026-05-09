/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:11:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static int	is_fd_redir_bonus(char **tok, int i, int e)
{
	if (i + 1 >= e)
		return (0);
	if (tok[i][0] == '\x02' && tok[i][1] >= '0' && tok[i][1] <= '2'
		&& tok[i][2] == '\0')
		return (1);
	return (0);
}

static int	handle_fd_redir_bonus(t_ast *n, char **tok, int *i, int e)
{
	int		sz;
	t_redir	*it;

	sz = tok[*i][1] - '0';
	(*i)++;
	if (handle_redir_bonus(n, tok, i, e))
		return (1);
	if (n->redirs)
	{
		it = n->redirs;
		while (it->next)
			it = it->next;
		it->redir_fd = sz;
	}
	return (0);
}

static int	is_redir_tok_bonus(char *s)
{
	return (ft_streq(s, "<") || ft_streq(s, ">") || ft_streq(s, ">>")
		|| ft_streq(s, "<<") || ft_streq(s, "<>") || ft_streq(s, "<<<"));
}

static int	fill_cmd_args_bonus(t_ast *n, char **tok, int s, int e)
{
	int	i;
	int	ac;

	i = s;
	ac = 0;
	while (i < e)
	{
		if (is_fd_redir_bonus(tok, i, e))
		{
			if (handle_fd_redir_bonus(n, tok, &i, e))
				return (1);
		}
		else if (is_redir_tok_bonus(tok[i]))
		{
			if (handle_redir_bonus(n, tok, &i, e))
				return (1);
		}
		else if (ft_streq(tok[i], "(") || ft_streq(tok[i], ")"))
			return (syn_err_bonus(tok[i]));
		else
			n->argv[ac++] = ft_strdup(tok[i]);
		i++;
	}
	return (0);
}

t_ast	*parse_simple_bonus(char **tok, int s, int e)
{
	t_ast	*n;
	int		sz;
	int		i;

	if (s >= e)
		return (NULL);
	n = new_node_bonus(NODE_CMD);
	sz = cmd_count_args_bonus(tok, s, e);
	n->argv = ft_gc_malloc(sizeof(char *) * (sz + 1));
	if (!n->argv)
		return (delete_ast_bonus(n), NULL);
	i = 0;
	while (i <= sz)
		n->argv[i++] = NULL;
	if (fill_cmd_args_bonus(n, tok, s, e))
		return (delete_ast_bonus(n), NULL);
	return (n);
}
