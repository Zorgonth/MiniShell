/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:02:50 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 11:34:14 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**my_split(t_commands *command)
{
	int		i;
	int		len;
	int		j;

	j = 0;
	i = 0;
	len = ft_counter(command->cmds);
	command->c_table = (char **)malloc(sizeof(char *) * (len + 1));
	while (command->cmds[i])
	{
		while (command->cmds[i] && (command->cmds[i] == ' '
				|| command->cmds[i] == '\t'))
			i++;
		if (command->cmds[i])
		{
			command->c_table[j] = ft_word1(command->cmds, i,
					ft_wordend1(command->cmds, i));
			j++;
			i = ft_wordend1(command->cmds, i);
		}
	}
	command->c_table[j] = 0;
	return (NULL);
}

char	*ft_word1(char *str, int start, int end)
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

int	ft_wordend1(char *s, int i)
{
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		i++;
	return (i);
}

int	ft_counter(char *str)
{
	int	i;
	int	count;
	int	flag;

	flag = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			flag = 1;
			i++;
		}
		if (flag)
		{
			count++;
			flag = 0;
		}
	}
	return (count);
}
