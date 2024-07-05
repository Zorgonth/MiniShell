/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:13:33 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/16 18:47:47 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_unset(t_terminal *terminal, t_commands *command)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (command->c_table[1])
	{
		while (command->c_table[i])
		{
			flag = ft_search(terminal, command->c_table[i]);
			if (flag == 1)
				remove_only_exp(terminal, command->c_table[i]);
			if (flag == 2)
				remove_both(terminal, command->c_table[i]);
			i++;
		}
	}
}

int	ft_search(t_terminal *terminal, char *str)
{
	int	i;

	i = 0;
	while (terminal->env[i])
	{
		if (ft_strncmp(terminal->env[i], str, ft_strlen(str)) == 0)
			return (2);
		i++;
	}
	i = 0;
	while (terminal->exp[i])
	{
		if (ft_strncmp(terminal->exp[i] + 11, str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	remove_only_exp(t_terminal *terminal, char *str)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = 0;
	while (terminal->exp[i])
	{
		if (ft_strncmp(terminal->exp[i] + 11, str, ft_strlen(str)) == 0)
			break ;
		i++;
	}
	while (terminal->exp[len])
		len++;
	tmp = (char **)malloc(sizeof(char *) * (len));
	tmp = remake(terminal->exp, i, tmp);
	ft_free_mat(terminal->exp);
	terminal->exp = tmp;
}

char	**remake(char **mat, int ind, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mat[i])
	{
		if (i == ind)
			i++;
		else
		{
			tmp[j] = ft_strdup(mat[i]);
			i++;
			j++;
		}
	}
	tmp[j] = 0;
	return (tmp);
}

void	remove_both(t_terminal *terminal, char *str)
{
	int		i;
	int		len;
	char	**tmp;

	remove_only_exp(terminal, str);
	i = 0;
	len = 0;
	while (terminal->env[i])
	{
		if (ft_strncmp(terminal->env[i], str, ft_strlen(str)) == 0)
			break ;
		i++;
	}
	while (terminal->env[len])
		len++;
	tmp = (char **)malloc(sizeof(char *) * (len));
	tmp = remake(terminal->env, i, tmp);
	ft_free_mat(terminal->env);
	terminal->env = tmp;
}
