/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:14:19 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 14:58:23 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strisnb(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	built_exit(t_terminal *terminal, t_commands	*command)
{
	terminal->exit = 1;
	if (command->c_table[1] && command->c_table[2])
		ft_putendl_fd("minishell: exit: Too many arguemnts", 2);
	else if (command->c_table[1] && ft_strisnb(command->c_table[1]) == 0)
	{
		terminal->exit = 255;
		write(2, "numeric argument required\n", 27);
	}
	else if (command->c_table[1])
		terminal->exit = ft_atoi(command->c_table[1]) % 255;
	exit(terminal->exit);
}
