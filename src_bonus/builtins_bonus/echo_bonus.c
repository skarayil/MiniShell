/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:21 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static int	is_nflag_bonus(const char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0' || i == 1)
		return (0);
	return (1);
}

int	ft_echo_bonus(t_shell *sh, char **argv)
{
	int	i;
	int	nl;

	(void)sh;
	i = 1;
	nl = 1;
	while (argv[i] && is_nflag_bonus(argv[i]))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
