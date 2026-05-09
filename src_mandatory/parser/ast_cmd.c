/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2026/02/09 09:02:43 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parser/parser.h"
#include "types.h"

int	syn_err(const char *tok)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, tok, ft_strlen(tok));
	write(2, "'\n", 2);
	return (1);
}

static int	get_redir_type(const char *op)
{
	if (ft_streq(op, "<"))
		return (R_IN);
	if (ft_streq(op, ">"))
		return (R_OUT);
	if (ft_streq(op, ">>"))
		return (R_APP);
	if (ft_streq(op, "<<"))
		return (R_HEREDOC);
	if (ft_streq(op, "<>"))
		return (R_INOUT);
	return (0);
}

int	handle_redir(t_ast *n, char **tok, int *i, int e)
{
	char	*op;
	int		type;

	op = tok[*i];
	(*i)++;
	if (*i >= e)
		return (syn_err("newline"));
	if (ft_streq(tok[*i], "<") || ft_streq(tok[*i], ">") || ft_streq(tok[*i],
			">>") || ft_streq(tok[*i], "<<") || ft_streq(tok[*i], "<>")
		|| ft_streq(tok[*i], "|"))
		return (syn_err(tok[*i]));
	type = get_redir_type(op);
	if (type)
		add_redir(n, type, tok[*i]);
	return (0);
}
