/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:47:24 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/15 16:04:47 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_cd(t_terminal *terminal, t_commands *command)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (command->c_table[len])
		len++;
	if (len > 2)
	{
		printf("hebss\n");
		return (-1);
	}
	if (!command->c_table[1] || ft_strncmp(command->c_table[1], "~", 1) == 0)
		update_pwd_home(terminal);
	else if (command->c_table[1])
	{
		if (chdir(command->c_table[1]) == -1)
		{
			printf("9lonj/errors");
		}
		else
			update_pwd(terminal);
	}
	return (0);
}
