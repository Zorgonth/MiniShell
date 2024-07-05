/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:37:28 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/16 10:39:23 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s;
	size_t		i;
	size_t		s_len;
	char		*res;
	size_t		j;

	s_len = (size_t)ft_strlen((char *)s1);
	j = s_len;
	i = 0;
	s = (char *)s1;
	while (ft_strchr(set, (int)s[i]) && s[i])
		i++;
	while (ft_strrchr(set, (int)s[j - 1]) && j > i)
		j--;
	res = (char *)malloc(j - i + 1);
	if (res == NULL)
		return (NULL);
	if (i == s_len)
	{
		res[0] = '\0';
		return (res);
	}
	ft_strlcpy(res, s1 + i, j - i + 1);
	return (res);
}
