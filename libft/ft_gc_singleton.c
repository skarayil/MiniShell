/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_singleton.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:52:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 10:52:00 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*ft_gc_singleton(int flag, t_data *data)
{
	static t_data	*instance;

	if (flag)
		instance = data;
	return (instance);
}
