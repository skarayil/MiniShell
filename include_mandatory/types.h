/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:06:37 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:06:38 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <signal.h>
# include <sys/types.h>

# define R_IN 1
# define R_OUT 2
# define R_APP 3
# define R_HEREDOC 4
# define R_INOUT 5

typedef struct s_fd_node	t_fd_node;

typedef struct s_fd_node
{
	int					fd;
	char				*tmp_file;
	struct s_fd_node	*next;
}						t_fd_node;

typedef struct s_shell
{
	char				**envp;
	int					last_exit_status;
	int					exit_code;
	int					running;
	int					default_path;
	t_fd_node			*fd_head;
}						t_shell;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					heredoc_fd;
	int					heredoc_expand;
	int					redir_fd;
	struct s_redir		*next;
}						t_redir;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_CMD,
	NODE_SEQ
}						t_node_type;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	char				**argv;
	t_redir				*redirs;
}						t_ast;

typedef enum e_sigmode
{
	SM_PROMPT,
	SM_HEREDOC
}						t_sigmode;

typedef struct s_sig_state
{
	volatile sig_atomic_t	sig;
	t_sigmode				mode;
}							t_sig_state;

typedef struct s_exp_context
{
	t_shell				*sh;
	char				*raw;
	char				***res;
	char				**buf;
	int					i;
	int					q;
}						t_exp_context;

typedef struct s_pl
{
	t_ast				**cmds;
	int					**fds;
	pid_t				*pids;
	int					n;
}						t_pl;

#endif
