/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:19 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/16 18:50:56 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_var(char *str, t_commands *command)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		write(command->out_fd, &str[i], 1);
		i++;
	}
}

void	built_echo2(t_commands *command, t_terminal *terminal, int i)
{
	while (command->cmds[i])
	{
		if (command->cmds[i] == '\"'
			|| command->cmds[i] == '\'')
			i = type(command, i + 1, command->cmds[i]);
		while (command->cmds[i] == ' ')
			i++;
		if (command->cmds[i] == '$')
			i = handle_var(command, terminal, i + 1);
		while (command->cmds[i] && command->cmds[i] != ' ')
		{
			write(command->out_fd, &command->cmds[i], 1);
			i++;
		}
		while (command->cmds[i] == ' ')
			i++;
		if ((int)(ft_strlen(command->cmds)) > i)
			write(1, " ", 1);
	}
}

void	update_exp2(t_terminal *terminal, int i, int j)
{
	int		a;
	char	**mat;

	a = 0;
	mat = (char **)malloc(sizeof(char *) * ((i - j) + 1));
	while (j < i)
	{
		mat[a] = ft_strdup(terminal->exp[j]);
		a++;
		j++;
	}
	mat[a] = 0;
	ft_free_mat(terminal->exp);
	terminal->exp = build_exp(terminal->env);
	a = 0;
	while (mat[a])
	{
		add_only_exp(mat[a], terminal);
		a++;
	}
	ft_free_mat(mat);
}
