/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:04:44 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "exec/exec.h"
#include "libft.h"
#include "types.h"

static t_fd_node	*create_fd_node(int fd, const char *tmp_file)
{
	t_fd_node	*node;

	node = (t_fd_node *)malloc(sizeof(t_fd_node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->tmp_file = NULL;
	if (tmp_file)
		node->tmp_file = ft_strdup(tmp_file);
	node->next = NULL;
	return (node);
}

void	ms_gc_add_fd(t_shell *sh, int fd, const char *tmp_file)
{
	t_fd_node	*node;

	if (fd < 0 || !sh)
		return ;
	node = create_fd_node(fd, tmp_file);
	if (!node)
		return ;
	node->next = sh->fd_head;
	sh->fd_head = node;
}

void	ms_gc_remove_fd(t_shell *sh, int fd)
{
	t_fd_node	*curr;
	t_fd_node	*prev;

	if (!sh)
		return ;
	curr = sh->fd_head;
	prev = NULL;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				sh->fd_head = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ms_gc_close_fd(t_shell *sh, int fd)
{
	if (fd >= 0)
		close(fd);
	ms_gc_remove_fd(sh, fd);
}

void	ms_gc_close_all(t_shell *sh)
{
	t_fd_node	*curr;
	t_fd_node	*next;

	if (!sh)
		return ;
	curr = sh->fd_head;
	while (curr)
	{
		next = curr->next;
		if (curr->fd >= 0)
			close(curr->fd);
		if (curr->tmp_file)
			unlink(curr->tmp_file);
		free(curr);
		curr = next;
	}
	sh->fd_head = NULL;
}
