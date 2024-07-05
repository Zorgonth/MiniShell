/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:43:25 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:17:29 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			flag = line[i++];
		while (line[i] && line[i] != flag)
			i++;
		if (line[i] == flag)
			flag = 0;
	}
	if (flag == 0)
		return (0);
	return (-1);
}

char	**get_path(char **env)
{
	char	**path;
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])))
			tmp = ft_substr(env[i], 0, ft_strlen(env[i]));
		i++;
	}
	path = ft_split(tmp + 5, ':');
	free(tmp);
	tmp = NULL;
	return (path);
}

char	*get_cmd_path(t_commands *com, char **env)
{
	int		i;
	char	**path;
	char	*end;
	char	*tmp;

	i = 0;
	path = get_path(env);
	while (path[i])
	{
		tmp = ft_basic_join(path[i], "/");
		end = ft_basic_join(tmp, com->c_table[0]);
		free(tmp);
		if (access(end, X_OK | F_OK) == 0)
			break ;
		free(end);
		end = NULL;
		i++;
	}
	ft_free_mat(path);
	return (end);
}

void	signals_main(void)
{
	signal(SIGINT, sig_type);
	signal(SIGQUIT, sig_type);
	clear_sigargs();
}

void	ft_free_tok(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		free(tokens->command->cmds);
		free(tokens->cmd);
		ft_free_mat(tokens->command->c_table);
		free(tokens->command);
		tmp = tmp->next;
		free(tokens);
		tokens = tmp;
	}
}
