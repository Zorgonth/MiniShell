/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:54 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/08/15 11:05:52 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_wordend(char const *s, char c, int i)
{
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_free(char **str, int x)
{
	int	i;

	i = 0;
	while (i < x && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (str);
}

int	ft_countwords(char const *s, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	if (s[i] != c && s[i] != '\0')
		words++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

char	*ft_word(char const *str, int start, int end)
{
	char	*s;
	int		j;

	j = 0;
	s = malloc(end - start + 1);
	if (s == NULL)
		return (NULL);
	if (str[start])
	{
		while (start < end)
		{
			s[j] = str[start];
			j++;
			start++;
		}
	}
	s[j] = '\0';
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	int			y;
	int			ind;

	ind = 0;
	y = 0;
	str = (char **)malloc((ft_countwords(s, c) + 1) * (sizeof(char *)));
	if (str == NULL)
		return (NULL);
	while (s[y] != '\0')
	{
		while (s[y] == c)
			y++;
		if (s[y] != c && s[y] != '\0')
		{
			str[ind] = ft_word(s, y, ft_wordend(s, c, y));
			if (str[ind++] == NULL)
				return (ft_free(str, ft_countwords(s, c)));
			y = ft_wordend(s, c, y);
		}
	}
	str[ind] = 0;
	return (str);
}
