/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:47:46 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 12:13:54 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fix_tokens(t_tokens **tokens)
{
	t_commands			*command;
	t_tokens			*head;

	head = *tokens;
	while (*tokens != NULL)
	{
		command = malloc(sizeof(t_commands));
		(*tokens)->command = command;
		(*tokens)->command->line = (*tokens)->cmd;
		(*tokens)->command->cmds = parser(*tokens);
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
	while (head != NULL)
	{
		bss(head);
		head = head->next;
	}
}

void	def(t_tokens *tokens)
{
	tokens->command->in_fd = 0;
	tokens->command->out_fd = 1;
	tokens->command->here_doc = -1;
}

int	redirections(t_commands *command, int *ind)
{
	if (command->cmds[(*ind)] == '<')
	{
		if (command->cmds[(*ind + 1)] == '>')
			return (-1);
		else if (command->cmds[(*ind + 1)] == '<')
		{
			command->here_doc = 1;
			(*ind)++;
		}
		else
			command->in_fd = ft_open(&command, *ind, 0);
	}
	else if (command->cmds[(*ind)] == '>')
	{
		if (command->cmds[(*ind + 1)] == '>'
			||command->cmds[(*ind + 1)] == '<')
			return (-1);
		else
			command->out_fd = ft_open(&command, *ind, 1);
	}
	return (0);
}

int	skip(char *line, int ind, char c)
{
	int	i;

	i = 0;
	while (line[ind] && line[ind] != c)
		ind++;
	if (line[ind] && line[ind] == c)
		return (ind + 1);
	else
		return (-1);
}

char	*parser(t_tokens *tokens)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(1, ft_strlen(tokens->command->line) + 1);
	while (tokens->command->line[i] == ' ')
		i++;
	while (tokens->command->line[i])
	{
		if (tokens->command->line[i] == '|')
		{
			i++;
			while (tokens->command->line[i] == ' ')
				i++;
		}
		else
			tmp[j++] = tokens->command->line[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
