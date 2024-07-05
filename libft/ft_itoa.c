/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:27:12 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/13 14:26:51 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int n)
{
	int	res;

	res = 1;
	while (n > 1)
	{
		res *= 10;
		n--;
	}
	return (res);
}

int	ft_all(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nb = (unsigned int)n * -1;
		i++;
	}
	else
		nb = (unsigned int)n;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_typee(char *s, int n, int i)
{
	int				a;
	unsigned int	nb;

	a = 0;
	if (n < 0)
	{
		nb = (unsigned int)n * -1;
		s[a] = '-';
		a++;
		i--;
	}
	else
		nb = (unsigned int)n;
	while (i > 0)
	{
		s[a] = ((nb / ft_pow(i)) + 48);
		nb = nb % ft_pow(i);
		a++;
		i--;
	}
	s[a] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;

	i = ft_all(n);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str = ft_typee(str, n, i);
	return (str);
}
