/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:00:48 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:17:20 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_terminal *terminal, int flag)
{
	int	i;

	i = -1;
	if (flag)
	{
		while (terminal->env[++i])
			free(terminal->env[i]);
		free(terminal->env);
		i = -1;
		while (terminal->exp[++i])
			free(terminal->exp[i]);
		free(terminal->exp);
		free(terminal);
	}
	if (flag == 2)
		exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_terminal			*terminal;
	t_tokens			*tokens;
	int					i;

	argc--;
	tokens = NULL;
	terminal = malloc(sizeof(t_terminal));
	if (building(terminal, envp) == -1)
		return (printf("Setup error!\n"), -1);
	while (1)
	{
		signals_main();
		i = ft_loop(terminal, &tokens, argv);
		if (i == -1)
			continue ;
		else if (i == -2)
			break ;
		exec(terminal, tokens);
		ft_free_tok(tokens);
	}
	return (clear_history(), ft_exit(terminal, 2), 0);
}

int	building(t_terminal *terminal, char **envp)
{
	signals_main();
	terminal->env = setup(envp);
	if (!terminal->env)
		return (-1);
	terminal->home = get_home(terminal->env);
	if (!terminal->home)
		return (-1);
	terminal->exp = build_exp(terminal->env);
	if (!terminal->env)
		return (-1);
	return (0);
}

int	ft_loop(t_terminal *terminal, t_tokens **tokens, char **argv)
{
	char	*line;

	line = NULL;
	prompt(argv, terminal);
	if (isatty(fileno(stdin)))
		line = readline(terminal->prompt);
	free(terminal->prompt);
	if (line && *line)
	{
		add_history(line);
		if (check_input(line) == 1)
		{
			printf("Syntax error!\n");
			free(line);
			return (-1);
		}
		if (ft_tok(terminal, tokens, line) == -1)
			return (-1);
	}
	else if (!line)
		return (-2);
	free(line);
	return (0);
}

int	ft_tok(t_terminal *terminal, t_tokens **tokens, char *line)
{
	t_tokens	*tmp;

	terminal->n_cmd = number_of_commands(line);
	if (terminal->n_cmd <= 0)
	{
		printf("No commands \n");
		return (-1);
	}
	*tokens = tokenizer(line, terminal->n_cmd);
	if (!tokens)
		return (-1);
	fix_tokens(tokens);
	tmp = *tokens;
	while (tmp)
	{
		my_split(tmp->command);
		tmp = tmp->next;
	}
	return (0);
}
