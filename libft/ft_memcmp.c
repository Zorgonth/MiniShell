/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:38:21 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/03 13:26:22 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*a;
	unsigned char		*b;
	size_t				i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (a[i] == b[i] && i < n - 1)
	{
		i++;
	}
	return (a[i] - b[i]);
}
