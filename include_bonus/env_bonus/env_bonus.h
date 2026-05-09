/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:24:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:24:34 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_BONUS_H
# define ENV_BONUS_H

# include "../types_bonus.h"

char	**env_copy_bonus(char **envp);
char	**env_init_minimal_bonus(char **envp);
void	env_free_bonus(char **envp);
int		env_increment_shlvl_bonus(char ***env);
int		env_update_underscore_bonus(t_shell *sh, char *val);
char	*env_get_bonus(t_shell *sh, const char *key);
int		env_len_bonus(char **envp);
int		env_key_is_valid_bonus(const char *s);
int		env_find_key_bonus(char **envp, const char *key);
int		env_set_bonus(t_shell *sh, const char *key, const char *val);
int		env_unset_bonus(t_shell *sh, const char *key);
void	env_print_export_sorted_bonus(t_shell *sh);
void	env_sort_envp_bonus(char **v, int n);
int		env_has_nonascii_bonus(const char *s);
void	env_print_val_dollar_bonus(const char *s, int i);
void	env_print_val_quoted_bonus(const char *s, int i);

#endif
