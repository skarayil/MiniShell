/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:25 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_bonus/parser_bonus.h"

static int	is_redir_op_bonus(const char *tok)
{
	return (ft_streq(tok, "<") || ft_streq(tok, ">") || ft_streq(tok, ">>")
		|| ft_streq(tok, "<<") || ft_streq(tok, "<>"));
}

int	cmd_count_args_bonus(char **tok, int s, int e)
{
	int	ac;
	int	i;

	ac = 0;
	i = s;
	while (i < e)
	{
		if (is_redir_op_bonus(tok[i]))
		{
			i++;
			if (i < e)
				i++;
		}
		else
		{
			ac++;
			i++;
		}
	}
	return (ac);
}
