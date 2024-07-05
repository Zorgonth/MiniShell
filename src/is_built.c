/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:53:40 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:01:38 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_commands	*command)
{
	if (!ft_strncmp(command->c_table[0], "cd",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "echo",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "unset",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "pwd",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "env",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "exit",
			ft_strlen(command->c_table[0])))
		return (0);
	else if (!ft_strncmp(command->c_table[0], "export",
			ft_strlen(command->c_table[0])))
		return (0);
	else
		return (1);
}

void	exec_builtin(t_terminal *terminal, t_commands *command, int flag)
{
	if (!ft_strncmp(command->c_table[0], "cd",
			ft_strlen(command->c_table[0])))
		built_cd(terminal, command);
	else if (!ft_strncmp(command->c_table[0], "echo",
			ft_strlen(command->c_table[0])))
		built_echo(command, terminal);
	if (!ft_strncmp(command->c_table[0], "export",
			ft_strlen(command->c_table[0])))
		built_export(terminal, command);
	else if (!ft_strncmp(command->c_table[0], "unset",
			ft_strlen(command->c_table[0])))
		built_unset(terminal, command);
	else if (!ft_strncmp(command->c_table[0], "pwd",
			ft_strlen(command->c_table[0])))
		built_pwd();
	else if (!ft_strncmp(command->c_table[0], "env",
			ft_strlen(command->c_table[0])))
		built_env(terminal);
	else if (!ft_strncmp(command->c_table[0], "exit",
			ft_strlen(command->c_table[0])))
		built_exit(terminal, command);
	if (flag)
		exit (0);
}
