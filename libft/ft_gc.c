/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:06:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 10:43:54 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_gc_init(void)
{
	static t_data	data;

	data.gc_head = NULL;
	ft_gc_singleton(1, &data);
}

static t_gc_node	*ft_gc_create_node(void *ptr)
{
	t_gc_node	*node;

	node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

static void	ft_gc_add_node(void *ptr)
{
	t_gc_node	*node;
	t_data		*data;

	if (!ptr)
		return ;
	data = ft_gc_singleton(0, NULL);
	if (!data)
		return ;
	node = ft_gc_create_node(ptr);
	if (!node)
		return ;
	node->next = data->gc_head;
	data->gc_head = node;
}

void	*ft_gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_gc_add_node(ptr);
	return (ptr);
}

void	ft_gc_destroy(void)
{
	t_gc_node	*current;
	t_gc_node	*next;
	t_data		*data;

	data = ft_gc_singleton(0, NULL);
	if (!data)
		return ;
	current = data->gc_head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	data->gc_head = NULL;
}
