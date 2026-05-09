/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:56 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "env_bonus/env_bonus.h"
#include "libft.h"
#include "types_bonus.h"

int	ft_unset_bonus(t_shell *sh, char **argv)
{
	int	i;
	int	rc;

	i = 1;
	rc = 0;
	if (argv[1] && argv[1][0] == '-')
	{
		write(2, "minishell: unset: -", 19);
		if (argv[1][1])
			write(2, &argv[1][1], 1);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	while (argv[i])
	{
		if (ft_streq(argv[i], "PATH"))
			sh->default_path = 0;
		env_unset_bonus(sh, argv[i]);
		i++;
	}
	return (rc);
}
