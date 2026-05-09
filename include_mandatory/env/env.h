/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:22:45 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:22:46 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../types.h"

char	**env_copy(char **envp);
char	**env_init_minimal(char **envp);
void	env_free(char **envp);
int		env_increment_shlvl(char ***env);
int		env_update_underscore(t_shell *sh, char *val);
char	*env_get(t_shell *sh, const char *key);
int		env_len(char **envp);
int		env_key_is_valid(const char *s);
int		env_find_key(char **envp, const char *key);
int		env_set(t_shell *sh, const char *key, const char *val);
int		env_unset(t_shell *sh, const char *key);
void	env_print_export_sorted(t_shell *sh);
void	env_sort_envp(char **v, int n);
int		env_has_nonascii(const char *s);
void	env_print_val_dollar(const char *s, int i);
void	env_print_val_quoted(const char *s, int i);

#endif
