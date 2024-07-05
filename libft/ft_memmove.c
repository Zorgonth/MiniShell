/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:03:39 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/12 15:48:43 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char					*a;
	unsigned char const				*b;
	int								i;

	a = (unsigned char *)dest;
	b = (unsigned char const *)src;
	if (src < dest && dest - src < (int)n)
	{
		i = n - 1;
		while (i >= 0)
		{
			a[i] = b[i];
			i--;
		}
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
