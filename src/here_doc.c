/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:59:48 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 14:59:30 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_delim(t_commands *command)
{
	int		i;
	char	*delim;
	int		j;

	i = 0;
	j = 0;
	while (command->cmds[i])
	{
		if (command->cmds[i] == '<')
		{
			i++;
			j = i;
			break ;
		}
		i++;
	}
	j++;
	while (command->cmds[j] == ' ')
		j++;
	i = j;
	while (command->cmds[j] && command->cmds[j] != ' ')
		j++;
	delim = ft_substr(command->cmds, i, j - i);
	return (delim);
}

void	reloc_mat(t_commands *command, int ind)
{
	int		i;
	int		j;
	char	**new;

	j = 0;
	i = -1;
	while (command->c_table[++i])
		;
	new = (char **)malloc(sizeof(char *) * (i - 1));
	i = 0;
	while (command->c_table[i])
	{
		if (i == ind || i == ind + 1)
			i++;
		else
		{
			new[j] = ft_strdup(command->c_table[i]);
			j++;
			i++;
		}
	}
	new[j] = 0;
	ft_free_mat(command->c_table);
	command->c_table = new;
}

char	*fix2(char *fixed, char *tmp, int end)
{
	char	*t;

	t = ft_substr(tmp, end, ft_strlen(tmp));
	free(tmp);
	fixed = ft_strjoin(fixed, " ");
	fixed = ft_strjoin(fixed, t);
	free(t);
	return (fixed);
}

void	fix_command(t_commands *command)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	j = 0;
	while (command->cmds[i] && command->cmds[i] != '<')
		i++;
	while (command->cmds[i])
	{
		if (command->cmds[i] == '<')
		{
			j = i;
			i += 2;
		}
		while (command->cmds[i] == ' ')
			i++;
		while (command->cmds[i] && command->cmds[i] != ' ')
			i++;
		break ;
	}
	tmp = command->cmds;
	command->cmds = ft_substr(tmp, 0, j);
	command->cmds = fix2(command->cmds, tmp, i);
}

int	open_hd(t_commands *command)
{
	int		i;
	char	*str;
	char	*delim;
	int		fd;

	i = 0;
	delim = get_delim(command);
	fix_command(command);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	while (1)
	{
		str = readline(">");
		if (!str || (!ft_strncmp(str, delim, ft_strlen(delim))
				&& !ft_strncmp(str, delim, ft_strlen(str))))
			break ;
		str = ft_strjoin(str, "\n");
		write(fd, str, ft_strlen(str) + 1);
		free(str);
	}
	free(delim);
	if (str)
		free(str);
	unlink("here_doc");
	close(fd);
	return (1);
}
