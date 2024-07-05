/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:51:30 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 14:50:43 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd(t_terminal *terminal)
{
	int		i;
	char	*tmp;

	i = 0;
	while (terminal->env[i])
	{
		if (ft_strncmp(terminal->env[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	free(terminal->env[i + 1]);
	tmp = ft_strdup(terminal->env[i]);
	terminal->env[i + 1] = ft_basic_join("OLD", tmp);
	free(tmp);
	free(terminal->env[i]);
	tmp = getcwd(NULL, 0);
	terminal->env[i] = ft_basic_join("PWD=", tmp);
	free(tmp);
	update_export(terminal);
}

void	update_pwd_home(t_terminal *terminal)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = -1;
	while (terminal->env[++i])
	{
		if (ft_strncmp(terminal->env[i], "PWD=", 4) == 0)
			break ;
	}
	while (terminal->env[j])
	{
		if (ft_strncmp(terminal->env[j], "HOME=", 5) == 0)
			break ;
		j++;
	}
	free(terminal->env[i + 1]);
	tmp = ft_strdup(terminal->env[i]);
	terminal->env[i + 1] = ft_basic_join("OLD", tmp);
	free(tmp);
	free(terminal->env[i]);
	terminal->env[i] = ft_basic_join("PWD=", terminal->env[j] + 5);
	chdir(terminal->env[j] + 5);
	update_export(terminal);
}

char	*ft_basic_join(char *s1, char *s2)
{
	char		*str;
	size_t		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len);
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len);
	return (str);
}

void	built_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
		printf("Pwd failed!\n");
	else
	{
		printf("%s\n", str);
		free(str);
	}
}
