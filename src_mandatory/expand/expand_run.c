/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:09:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "expand/expand.h"
#include "libft.h"
#include "types.h"

static int	expand_redir_single(t_shell *sh, t_redir *r)
{
	char	**res;
	int		count;

	if (r->type == R_HEREDOC)
		return (0);
	res = expand_token(sh, r->file);
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

char	**expand_list(t_shell *sh, char **argv)
{
	char	**final;
	char	**part;
	int		i;
	int		j;

	final = NULL;
	i = 0;
	while (argv && argv[i])
	{
		part = expand_token(sh, argv[i]);
		j = 0;
		while (part && part[j])
		{
			final = exp_arr_add(final, part[j]);
			j++;
		}
		i++;
	}
	return (final);
}

int	expand_redirs(t_shell *sh, t_redir *r)
{
	while (r)
	{
		if (expand_redir_single(sh, r) != 0)
			return (1);
		r = r->next;
	}
	return (0);
}
