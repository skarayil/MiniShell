/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:11:07 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

int	syn_err_bonus(const char *tok)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, tok, ft_strlen(tok));
	write(2, "'\n", 2);
	return (1);
}

static int	get_redir_type_bonus(const char *op)
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

int	handle_redir_bonus(t_ast *n, char **tok, int *i, int e)
{
	char	*op;
	int		type;

	op = tok[*i];
	(*i)++;
	if (*i >= e)
		return (syn_err_bonus("newline"));
	if (ft_streq(tok[*i], "<") || ft_streq(tok[*i], ">") || ft_streq(tok[*i],
			">>") || ft_streq(tok[*i], "<<") || ft_streq(tok[*i], "|")
		|| ft_streq(tok[*i], "||") || ft_streq(tok[*i], "&&")
		|| ft_streq(tok[*i], "(") || ft_streq(tok[*i], "<>"))
		return (syn_err_bonus(tok[*i]));
	type = get_redir_type_bonus(op);
	if (type)
		add_redir_bonus(n, type, tok[*i]);
	return (0);
}
