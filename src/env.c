/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:08:53 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 11:51:38 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_env(t_terminal *terminal)
{
	int	i;

	i = 0;
	while (terminal->env[i])
	{
		printf("%s\n", terminal->env[i]);
		i++;
	}
}

char	**copy_env(char **env, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	**res;

	j = 0;
	i = 0;
	res = (char **)malloc(sizeof(char *) * (len + 1));
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		res[i] = ft_basic_join("declare -x ", tmp);
		free(tmp);
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**build_exp(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
		i++;
	res = copy_env(env, i);
	return (res);
}

void	built_export(t_terminal *terminal, t_commands *command)
{
	int	i;
	int	flag;

	i = 0;
	if (!command->c_table[1])
		ft_type_exp(terminal);
	else
	{
		flag = check_name(command->c_table[1]);
		if (flag == -1)
			printf("error\n");
		if (flag == 2)
			add_only_exp(command->c_table[1], terminal);
		if (flag == 3)
			add_both(command->c_table[1], terminal);
	}
}

void	ft_type_exp(t_terminal *terminal)
{
	int	i;

	i = 0;
	while (terminal->exp[i])
	{
		printf("%s\n", terminal->exp[i]);
		i++;
	}
}
