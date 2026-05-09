/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:31:45 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/09 09:04:16 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../types.h"

int		exec_ast(t_shell *sh, t_ast *node);
int		exec_pipe(t_shell *sh, t_ast *node);
int		exec_cmd(t_shell *sh, t_ast *node);
int		exec_external(t_shell *sh, t_ast *node, char **xv);
int		exec_builtin(t_shell *sh, t_ast *node, char **xv);
int		exec_cmd_empty(t_shell *sh, t_ast *node, char **xv);
void	exec_child_execve(t_shell *sh, char **argv);
char	*find_in_path(t_shell *sh, const char *cmd);
int		redir_apply_child(t_shell *sh, t_redir *r);
int		redir_apply_parent(t_shell *sh, t_redir *r, int *save_in,
			int *save_out);
void	redir_restore_parent(t_shell *sh, int save_in, int save_out);
int		op_in(t_shell *sh, char *file, int *saved);
int		op_out(t_shell *sh, t_redir *r, int *saved);
int		op_in_out(t_shell *sh, char *file, int *saved_in);
int		op_heredoc(t_shell *sh, t_redir *r, int *saved);
int		run_heredoc(t_shell *sh, t_redir *r);
int		hd_loop(t_shell *sh, t_redir *r, int fd);
void	ms_gc_add_fd(t_shell *sh, int fd, const char *tmp_file);
void	ms_gc_remove_fd(t_shell *sh, int fd);
void	ms_gc_close_fd(t_shell *sh, int fd);
void	ms_gc_close_all(t_shell *sh);

#endif
