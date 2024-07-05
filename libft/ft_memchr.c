/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:23:53 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/03 13:23:59 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*a;
	size_t		i;

	i = 0;
	a = (const char *)s;
	while (i < n)
	{
		if (a[i] == (char)c)
		{
			return ((void *)(a + i));
		}
		i++;
	}
	return (0);
}
