/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:35:03 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/06 21:18:54 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	size_t	*dup;

	total = nmemb * size;
	dup = malloc(total);
	if (!dup)
		return (NULL);
	ft_memset(dup, 0, total);
	return (dup);
}
