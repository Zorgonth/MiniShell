/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:57:28 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 11:58:42 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	if (str[0] && str[0] == '_')
		return (printf("Not a valid identifier\n"), -1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (printf("Not a valid identifier\n"), -1);
		i++;
	}
	if (str[i] != '=')
		return (2);
	if (str[i] == '=')
	{
		i++;
		if (!str[i])
			return (2);
		else
			return (3);
	}
	return (0);
}

void	add_only_exp(char *str, t_terminal *terminal)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	i = 0;
	j = 0;
	while (terminal->exp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (terminal->exp[i])
	{
		new[j] = ft_strdup(terminal->exp[i]);
		i++;
		j++;
	}
	tmp = ft_strdup(str);
	new[j++] = ft_basic_join("declare -x ", tmp);
	free(tmp);
	new[j] = 0;
	ft_free_mat(terminal->exp);
	terminal->exp = new;
}

void	add_both(char *str, t_terminal *terminal)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	add_only_exp(str, terminal);
	while (terminal->env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	new[j++] = ft_strdup(str);
	i = 0;
	while (terminal->env[i])
	{
		new[j] = ft_strdup(terminal->env[i]);
		i++;
		j++;
	}
	new[j] = 0;
	ft_free_mat(terminal->env);
	terminal->env = new;
}

void	ft_free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	update_export(t_terminal *terminal)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (terminal->exp[i])
		i++;
	while (terminal->env[j])
		j++;
	if (i == j)
	{
		ft_free_mat(terminal->exp);
		terminal->exp = build_exp(terminal->env);
	}
	if (i != j)
		update_exp2(terminal, i, j);
}
