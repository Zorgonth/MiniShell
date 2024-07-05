/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:55:39 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:02:58 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fix_cmds(t_commands **command, int end, int start)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
	tmp = ft_strdup((*command)->cmds);
	free((*command)->cmds);
	(*command)->cmds = calloc(1, ft_strlen(tmp));
	while (tmp[i])
	{
		if (i >= start && i <= end)
			i++;
		else
		{
			(*command)->cmds[j] = tmp[i];
			i++;
			j++;
		}
	}
	(*command)->cmds[j] = '\0';
	free(tmp);
}

char	*get_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

int	check2(char *line, int i)
{
	if (line[i] && (line[i] == '*' || line[i] == '#'
			|| line[i] == '&' || line[i] == '!' || line[i] == '('
			|| line[i] == ')' || line [i] == '{' || line[i] == '}'
			|| line[i] == '[' || line[i] == ']' || line[i] == ';'))
		return (1);
	return (0);
}

int	check3(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			i++;
			if (line[i] && line[i] == '<')
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (!line[i])
					return (1);
			}
		}
		i++;
	}
	return (0);
}
