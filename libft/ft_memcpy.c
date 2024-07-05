/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:04:18 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/03 13:22:37 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*a;
	const char		*b;
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	a = (char *)dest;
	b = (const char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}
