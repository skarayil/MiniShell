/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:24:42 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:24:43 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

# include "../types_bonus.h"

int		exec_ast_bonus(t_shell *sh, t_ast *node);
int		exec_pipe_bonus(t_shell *sh, t_ast *node);
int		exec_subshell_bonus(t_shell *sh, t_ast *node);
int		exec_cmd_bonus(t_shell *sh, t_ast *node);
int		exec_external_bonus(t_shell *sh, t_ast *node, char **xv);
int		exec_builtin_bonus(t_shell *sh, t_ast *node, char **xv);
int		exec_cmd_empty_bonus(t_shell *sh, t_ast *node, char **xv);
void	exec_child_execve_bonus(t_shell *sh, char **argv);
char	*find_in_path_bonus(t_shell *sh, const char *cmd);
int		redir_apply_child_bonus(t_shell *sh, t_redir *r);
int		redir_apply_parent_bonus(t_shell *sh, t_redir *r, int *save_in,
			int *save_out);
void	redir_restore_parent_bonus(t_shell *sh, int save_in, int save_out);
int		op_in_bonus(t_shell *sh, char *file, int *saved);
int		op_out_bonus(t_shell *sh, t_redir *r, int *saved);
int		op_heredoc_bonus(t_shell *sh, t_redir *r, int *saved);
int		op_in_out_bonus(t_shell *sh, char *file, int *saved_in);
void	run_herestring_bonus(t_shell *sh, t_redir *r);
int		run_heredoc_bonus(t_shell *sh, t_redir *r);
int		hd_loop_bonus(t_shell *sh, t_redir *r, int fd);
void	ms_gc_add_fd_bonus(t_shell *sh, int fd, const char *tmp_file);
void	ms_gc_remove_fd_bonus(t_shell *sh, int fd);
void	ms_gc_close_fd_bonus(t_shell *sh, int fd);
void	ms_gc_close_all_bonus(t_shell *sh);

#endif
