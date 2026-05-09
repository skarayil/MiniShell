/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:14:24 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtins/builtins.h"
#include "libft.h"
#include "types.h"

int	ft_pwd(t_shell *sh, char **argv)
{
	char	buf[4096];
	char	*cwd;

	(void)sh;
	(void)argv;
	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
		return (perror("pwd"), 1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}
