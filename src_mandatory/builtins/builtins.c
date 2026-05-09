/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:13:43 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:05 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include "types.h"

int	is_builtin(const char *s)
{
	if (ft_streq(s, "echo"))
		return (1);
	if (ft_streq(s, "cd"))
		return (1);
	if (ft_streq(s, "pwd"))
		return (1);
	if (ft_streq(s, "export"))
		return (1);
	if (ft_streq(s, "unset"))
		return (1);
	if (ft_streq(s, "exit"))
		return (1);
	if (ft_streq(s, "env"))
		return (1);
	return (0);
}

int	run_builtin(t_shell *sh, char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_streq(argv[0], "echo"))
		return (ft_echo(sh, argv));
	if (ft_streq(argv[0], "cd"))
		return (ft_cd(sh, argv));
	if (ft_streq(argv[0], "pwd"))
		return (ft_pwd(sh, argv));
	if (ft_streq(argv[0], "export"))
		return (ft_export(sh, argv));
	if (ft_streq(argv[0], "unset"))
		return (ft_unset(sh, argv));
	if (ft_streq(argv[0], "exit"))
		return (ft_exit(sh, argv));
	if (ft_streq(argv[0], "env"))
		return (ft_env(sh, argv));
	return (1);
}
