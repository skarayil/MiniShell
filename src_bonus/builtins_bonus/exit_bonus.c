/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 19:18:50 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static int	exit_err_bonus(t_shell *sh, char **argv)
{
	write(2, "minishell: exit: ", 17);
	write(2, argv[1], ft_strlen(argv[1]));
	write(2, ": numeric argument required\n", 28);
	sh->exit_code = 2;
	sh->running = 0;
	return (2);
}

int	ft_exit_bonus(t_shell *sh, char **argv)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	if (!argv[1])
	{
		sh->exit_code = sh->last_exit_status;
		sh->running = 0;
		return (sh->exit_code);
	}
	if (!exit_is_num_bonus(argv[1]) || exit_check_overflow_bonus(argv[1]))
		return (exit_err_bonus(sh, argv));
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	sh->exit_code = exit_to_code_bonus(argv[1]);
	sh->running = 0;
	return (sh->exit_code);
}
