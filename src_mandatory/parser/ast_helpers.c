/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:00:00 by 42                #+#    #+#             */
/*   Updated: 2026/02/09 08:25:04 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/parser.h"

int	find_op(char **tok, int s, int e, char *op)
{
	int	i;

	i = e - 1;
	while (i >= s)
	{
		if (ft_streq(tok[i], op))
			return (i);
		i--;
	}
	return (-1);
}
