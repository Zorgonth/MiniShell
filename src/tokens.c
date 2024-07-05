/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:55:42 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/16 18:46:31 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokens	*tokenizer(char *line, int n_cmd)
{
	t_tokens	*head;
	t_tokens	*curr;
	int			i;

	i = 0;
	if (n_cmd > 0)
	{
		head = (t_tokens *)malloc(sizeof(t_tokens));
		head->next = NULL;
	}
	else
		return (NULL);
	curr = head;
	while (i < n_cmd - 1)
	{
		curr->next = (t_tokens *)malloc(sizeof(t_tokens));
		curr = curr->next;
		curr->next = NULL;
		i++;
	}
	if (get_tokens(&head, line) == -1)
		return (NULL);
	return (head);
}

int	get_tokens(t_tokens **head, char *line)
{
	int			i;
	int			start;
	t_tokens	*curr;

	curr = *head;
	start = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			curr->cmd = ft_substr(line, start, i - start);
			start = i;
			if (curr->next != NULL)
				curr = curr->next;
		}
	}
	curr->cmd = ft_substr(line, start, i - start);
	return (0);
}
