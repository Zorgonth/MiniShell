/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:58 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/04/12 12:46:16 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;

	if (size && SIZE_MAX / size < nmemb)
		return (NULL);
	s = malloc(size * nmemb);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return (s);
}
