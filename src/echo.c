/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:14 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 12:41:40 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_echo(t_commands *command, t_terminal *terminal)
{
	int	i;
	int	flag;

	flag = find_dash(&command);
	i = 0;
	while (command->cmds[i] && command->cmds[i] != ' ')
		i++;
	while (command->cmds[i] == ' ')
		i++;
	built_echo2(command, terminal, i);
	if (!flag)
		write(command->out_fd, "\n", 1);
}

int	type(t_commands *command, int start, char c)
{
	while (command->cmds[start] != c)
	{
		write(command->out_fd, &command->cmds[start], 1);
		start++;
	}
	if ((int)(ft_strlen(command->cmds)) > start + 1)
		write(command->out_fd, " ", 1);
	return (start + 1);
}

int	find_dash(t_commands **command)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while ((*command)->cmds[++i])
	{
		if ((*command)->cmds[i] && ((*command)->cmds[i] == '\"'
				|| (*command)->cmds[i] == '\''))
			i = skip((*command)->cmds, i + 1, (*command)->cmds[i]);
		if (!(*command)->cmds[i])
			break ;
		if ((*command)->cmds[i] == '-' && (*command)->cmds[i - 1] == ' ')
		{
			if ((*command)->cmds[i + 1] && (*command)->cmds[i + 1] == 'n')
			{
				flag = ft_rl(command, i);
				i = 0;
			}
			else
				break ;
		}
	}
	return (flag);
}

int	ft_rl(t_commands **command, int start)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = ft_strdup((*command)->cmds);
	free((*command)->cmds);
	(*command)->cmds = ft_calloc(1, ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		if (i == start)
		{
			i++;
			while (tmp[i] == 'n')
				i++;
		}
		else
			(*command)->cmds[j++] = tmp[i++];
	}
	free(tmp);
	(*command)->cmds[j] = '\0';
	return (1);
}

int	handle_var(t_commands *command, t_terminal *terminal, int ind)
{
	int		i;
	char	*tmp;

	i = 0;
	while (command->cmds[ind] && command->cmds[ind] != ' ')
	{
		ind++;
		i++;
	}
	tmp = ft_substr(command->cmds, ind - i, ind);
	i = 0;
	while (terminal->exp[i])
	{
		if (ft_strncmp(terminal->exp[i] + 11, tmp, ft_strlen(tmp) - 1) == 0)
		{
			print_var(terminal->exp[i], command);
			break ;
		}
		i++;
	}
	free(tmp);
	return (ind + 1);
}
