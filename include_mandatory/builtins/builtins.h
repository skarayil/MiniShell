/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:05:59 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:06:00 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../types.h"

int	is_builtin(const char *cmd);
int	run_builtin(t_shell *sh, char **argv);
int	ft_pwd(t_shell *sh, char **argv);
int	ft_cd(t_shell *sh, char **argv);
int	ft_echo(t_shell *sh, char **argv);
int	ft_exit(t_shell *sh, char **argv);
int	exit_is_num(const char *s);
int	exit_check_overflow(const char *str);
int	exit_to_code(const char *s);
int	ft_export(t_shell *sh, char **argv);
int	ft_unset(t_shell *sh, char **argv);
int	ft_env(t_shell *sh, char **argv);

#endif
