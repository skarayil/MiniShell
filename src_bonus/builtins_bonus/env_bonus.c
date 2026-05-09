/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:28 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "libft.h"
#include "types_bonus.h"

int	ft_env_bonus(t_shell *sh, char **argv)
{
	int	i;

	if (argv[1])
	{
		write(2, "env: '", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "': No such file or directory\n", 29);
		return (127);
	}
	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (ft_strchr(sh->envp[i], '='))
		{
			write(1, sh->envp[i], ft_strlen(sh->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
