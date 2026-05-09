/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:04:15 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:04:16 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

# include "../types_bonus.h"

int	is_builtin_bonus(const char *cmd);
int	run_builtin_bonus(t_shell *sh, char **argv);
int	ft_pwd_bonus(t_shell *sh, char **argv);
int	ft_cd_bonus(t_shell *sh, char **argv);
int	ft_echo_bonus(t_shell *sh, char **argv);
int	ft_exit_bonus(t_shell *sh, char **argv);
int	exit_is_num_bonus(const char *s);
int	exit_check_overflow_bonus(const char *str);
int	exit_to_code_bonus(const char *s);
int	ft_export_bonus(t_shell *sh, char **argv);
int	ft_unset_bonus(t_shell *sh, char **argv);
int	ft_env_bonus(t_shell *sh, char **argv);

#endif
