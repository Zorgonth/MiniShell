/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:46:27 by rmehadje          #+#    #+#             */
/*   Updated: 2024/02/17 15:28:25 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_commands *cmd, char **env, int tmp)
{
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	if (cmd->in_fd > 2)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd > 2)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	if (execve(get_cmd_path(cmd, env), cmd->c_table, env) == -1)
		printf("cannot execute!\n");
}

int	exec3(t_terminal *term, t_tokens *tokens, int tmp, int *fd)
{
	if (tokens->command->here_doc == 1)
		open_hd(tokens->command);
	if (is_builtin(tokens->command) == 0)
		exec_builtin(term, tokens->command, 0);
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(tokens->command, term->env, tmp);
	}
	close(fd[1]);
	close(tmp);
	tmp = fd[0];
	return (tmp);
}

void	exec(t_terminal *term, t_tokens *tokens)
{
	int	tmp;
	int	fd[2];

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tmp = dup(STDIN_FILENO);
	while (tokens)
	{
		if (!tokens->next)
			tmp = exec2(term, tokens, tmp);
		else
			tmp = exec3(term, tokens, tmp, fd);
		tokens = tokens->next;
	}
	close(tmp);
}

int	exec2(t_terminal *term, t_tokens *tokens, int tmp)
{
	if (tokens->command->here_doc == 1)
		open_hd(tokens->command);
	if (is_builtin(tokens->command) == 0)
		exec_builtin(term, tokens->command, 0);
	else if (fork() == 0)
		execute(tokens->command, term->env, tmp);
	close(tmp);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
	tmp = dup(STDIN_FILENO);
	return (tmp);
}
