/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:25:29 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 14:44:47 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bss(t_tokens	*tokens)
{
	int	i;

	i = 0;
	def(tokens);
	while (tokens->command->cmds[i])
	{
		if (tokens->command->cmds[i] == '\"'
			|| tokens->command->cmds[i] == '\'')
			i = skip(tokens->command->cmds, i + 1, tokens->command->cmds[i]);
		if (tokens->command->cmds[i]
			&& (tokens->command->cmds[i] == '<'
				|| tokens->command->cmds[i] == '>'))
		{
			if (tokens->command->cmds[i] == '<')
				redirections(tokens->command, &i);
			else if (tokens->command->cmds[i] == '>')
				redirections(tokens->command, &i);
		}
		if (tokens->command->cmds[i])
			i++;
	}
}

int	ft_open(t_commands **command, int ind, int flag)
{
	char	*tmp;
	int		fd;

	fd = 0;
	tmp = ft_name(command, ind, flag);
	if (flag == 0)
	{
		if (access(tmp, F_OK) == 0 && access(tmp, R_OK) == 0)
			fd = open(tmp, O_RDONLY);
	}
	else
		fd = open(tmp, O_APPEND | O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(tmp);
	return (fd);
}

void	ft_two(char *name, int *ind, int flag)
{
	while (name[(*ind)] == ' ')
		(*ind)++;
	if (flag == 0)
	{
		while (name[(*ind)])
		{
			if (name[(*ind)] != '>' && name[(*ind)] != '\''
				&& name[(*ind)] != '\"' && name[(*ind)] != ' ')
				(*ind)++;
			else
				break ;
		}
	}
	else
	{
		while (name[(*ind)])
		{
			if (name[(*ind)] != '<' && name[(*ind)] != '\''
				&& name[(*ind)] != '\"' && name[(*ind)] != ' ')
				(*ind)++;
			else
				break ;
		}
	}
}

char	*ft_name(t_commands **command, int ind, char flag)
{
	char	*tmp;
	int		j;

	ind++;
	j = ind;
	tmp = NULL;
	ft_two((*command)->cmds, &ind, flag);
	tmp = fix_name((*command)->cmds, ind, j);
	fix_cmds(command, ind - 1, j - 1);
	return (tmp);
}

char	*fix_name(char *name, int end, int start)
{
	int		i;
	char	*tmp;
	int		len;

	len = end - start;
	i = 0;
	tmp = calloc(1, len + 1);
	while (name[start] == ' ')
	{
		start++;
		len--;
	}
	while (name[start] && len >= 0 && name[start] != ' ')
	{
		tmp[i++] = name[start++];
		len--;
	}
	tmp[i] = '\0';
	return (tmp);
}
