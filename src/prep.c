/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:02:40 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 14:15:42 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_input(char *line)
{
	int	i;
	int	flag;
	int	chr;

	flag = 0;
	i = -1;
	if (check3(line) == 1)
		return (1);
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			chr = line[i++];
			flag = 1;
		}
		while (line[i] && line[i] != chr && flag)
			i++;
		if (!line[i])
			break ;
		if (line[i] && line[i] == chr && flag)
			flag = 0;
		if (check2(line, i) == 1)
			return (1);
	}
	return (flag);
}

void	prompt(char **argv, t_terminal *terminal)
{
	char	*user;
	char	*tmp;

	argv = NULL;
	tmp = getenv("USER");
	user = ft_basic_join(tmp, " % ");
	terminal->prompt = ft_basic_join("~> ", user);
	free(user);
}

char	**setup(char **envp)
{
	char	**env;
	int		i;

	i = -1;
	while (envp[++i])
		;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = 0;
	return (env);
}

int	number_of_commands(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	if (line[0])
		n = 1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			if (check_pipe(line, i) == -1)
				return (0);
			n++;
		}
	}
	return (n);
}

int	check_pipe(char *line, int ind)
{
	int	i;

	i = 0;
	ind++;
	while (line[ind])
	{
		if (line[ind] != ' ')
			i = 1;
		ind++;
	}
	if (i)
		return (0);
	return (-1);
}
