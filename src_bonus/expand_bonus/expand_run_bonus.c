/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_run_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:24 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "expand_bonus/expand_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static int	expand_redir_single_bonus(t_shell *sh, t_redir *r)
{
	char	**res;
	int		count;

	if (r->type == R_HEREDOC || r->type == R_HERESTR)
		return (0);
	res = expand_token_bonus(sh, r->file);
	count = 0;
	while (res && res[count])
		count++;
	if (count != 1)
	{
		write(2, "minishell: ", 11);
		write(2, r->file, ft_strlen(r->file));
		write(2, ": ambiguous redirect\n", 21);
		return (1);
	}
	r->file = res[0];
	return (0);
}

char	**expand_list_bonus(t_shell *sh, char **argv)
{
	char	**final;
	char	**part;
	int		i;
	int		j;

	final = NULL;
	i = 0;
	while (argv && argv[i])
	{
		part = expand_token_bonus(sh, argv[i]);
		j = 0;
		while (part && part[j])
		{
			final = exp_arr_add_bonus(final, part[j]);
			j++;
		}
		i++;
	}
	return (final);
}

int	expand_redirs_bonus(t_shell *sh, t_redir *r)
{
	while (r)
	{
		if (expand_redir_single_bonus(sh, r) != 0)
			return (1);
		r = r->next;
	}
	return (0);
}
