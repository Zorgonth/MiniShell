/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:04:00 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:02:24 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ctrl_bs(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	sig_type(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_bs();
}

void	block_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	clear_sigargs(void)
{
	struct termios	arg;

	tcgetattr(1, &arg);
	arg.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &arg);
}
