/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:33:25 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/16 10:41:00 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	j;

	if (start >= (unsigned int)ft_strlen((char *)s))
		return (ft_strdup(""));
	i = ft_strlen((char *)s + start);
	if (i > len)
		i = len;
	a = (char *)malloc(i + 1);
	if (!a)
		return (NULL);
	j = 0;
	while (j < i)
	{
		a[j] = s[start + j];
		j++;
	}
	a[j] = '\0';
	return (a);
}
