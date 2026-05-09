/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:23:01 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus/builtins_bonus.h"
#include "libft.h"
#include "types_bonus.h"

int	is_builtin_bonus(const char *s)
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

int	run_builtin_bonus(t_shell *sh, char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_streq(argv[0], "echo"))
		return (ft_echo_bonus(sh, argv));
	if (ft_streq(argv[0], "cd"))
		return (ft_cd_bonus(sh, argv));
	if (ft_streq(argv[0], "pwd"))
		return (ft_pwd_bonus(sh, argv));
	if (ft_streq(argv[0], "export"))
		return (ft_export_bonus(sh, argv));
	if (ft_streq(argv[0], "unset"))
		return (ft_unset_bonus(sh, argv));
	if (ft_streq(argv[0], "exit"))
		return (ft_exit_bonus(sh, argv));
	if (ft_streq(argv[0], "env"))
		return (ft_env_bonus(sh, argv));
	return (1);
}
