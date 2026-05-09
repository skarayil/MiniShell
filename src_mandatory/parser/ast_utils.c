/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:45:30 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/09 08:25:04 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"

static int	is_redir_op(const char *tok)
{
	return (ft_streq(tok, "<") || ft_streq(tok, ">") || ft_streq(tok, ">>")
		|| ft_streq(tok, "<<") || ft_streq(tok, "<>"));
}

int	cmd_count_args(char **tok, int s, int e)
{
	int	ac;
	int	i;

	ac = 0;
	i = s;
	while (i < e)
	{
		if (is_redir_op(tok[i]))
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
