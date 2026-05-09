/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_input_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:13:08 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"
#include "minishell_bonus.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static int	is_trailing_op_bonus(char *s)
{
	return (ft_streq(s, "|") || ft_streq(s, "&&") || ft_streq(s, "||")
		|| ft_streq(s, "<") || ft_streq(s, ">") || ft_streq(s, "<<")
		|| ft_streq(s, ">>") || ft_streq(s, "<>"));
}

static int	check_trailing_bonus(t_shell *sh, char *line)
{
	char	**tok;
	int		len;
	int		ret;

	tok = tokenize_bonus(sh, line);
	if (!tok)
		return (0);
	len = 0;
	while (tok[len])
		len++;
	ret = 0;
	if (len > 0 && (ft_streq(tok[len - 1], "|") || ft_streq(tok[len - 1],
				"&&") || ft_streq(tok[len - 1], "||")))
	{
		if (len == 1)
			ret = 0;
		else if (is_trailing_op_bonus(tok[len - 2]))
			ret = 0;
		else
			ret = 1;
	}
	argv_free_bonus(tok);
	return (ret);
}

int	is_incomplete_bonus(t_shell *sh, char *line)
{
	return (check_trailing_bonus(sh, line));
}
