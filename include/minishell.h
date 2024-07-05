/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:22:14 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/02/17 15:19:36 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

enum	e_tokens
{
	CMD = 0,
	BUILTIN,
	ARG,
	REDIRECT,
	PIPE,
	FD,
	HERE_DOC,
};

typedef struct s_commands
{
	char	*line;
	char	*cmds;
	char	**c_table;
	int		in_fd;
	int		out_fd;
	int		here_doc;
}	t_commands;

typedef struct s_tokens
{
	char				*cmd;
	struct s_tokens		*next;
	struct s_commands	*command;
}	t_tokens;

typedef struct s_terminal
{
	char	*input;
	char	*clean;
	char	*prompt;
	char	**argv;
	char	**env;
	char	**exp;
	char	*home;
	int		n_cmd;
	int		exit;
}		t_terminal;

void		prompt(char **argv, t_terminal *terminal);
int			main(int argc, char **argv, char **envp);
char		**setup(char **envp);
t_tokens	*tokenizer(char *line, int n_cmds);
int			check_pipe(char *line, int ind);
int			get_tokens(t_tokens **head, char *line);
int			number_of_commands(char *line);
void		fix_tokens(t_tokens **tokens);
int			check_input(char *line);
int			check_quotes(char *line);
char		*parser(t_tokens *tokens);
int			skip(char *line, int ind, char c);
int			redirections(t_commands *command, int *ind);
void		def(t_tokens *tokens);
void		bss(t_tokens	*tokens);
int			ft_open(t_commands **command, int ind, int flag);
char		*ft_name(t_commands **command, int ind, char flag);
char		*fix_name(char *name, int end, int start);
void		ft_two(char *name, int *ind, int flag);
void		fix_cmds(t_commands **command, int end, int start);

int			ft_rl(t_commands **command, int start);
int			find_dash(t_commands **command);
void		built_echo(t_commands *command, t_terminal *terminal);
int			type(t_commands *command, int start, char c);
// char	**my_fucking_split(char *str);
// int	ft_count_len(char *str);
char		**my_split(t_commands *command);
int			ft_counter(char *str);
char		*ft_word1(char *str, int start, int end);
int			ft_wordend1(char *s, int i);
void		update_pwd(t_terminal *terminal);
void		update_pwd_home(t_terminal *terminal);
char		*ft_basic_join(char *s1, char *s2);
int			built_cd(t_terminal *terminal, t_commands *command);
char		*get_home(char **env);
char		**build_exp(char **env);
char		**copy_env(char **env, int len);
void		built_env(t_terminal *terminal);
void		ft_type_exp(t_terminal *terminal);
void		add_only_exp(char *str, t_terminal *terminal);
int			check_name(char *str);
void		built_export(t_terminal *terminal, t_commands *command);
void		ft_free_mat(char **mat);
void		add_both(char *str, t_terminal *terminal);
int			ft_search(t_terminal *terminal, char *str);
void		built_unset(t_terminal *terminal, t_commands *command);
char		**remake(char	**mat, int ind, char **tmp);
void		remove_only_exp(t_terminal *terminal, char *str);
void		remove_both(t_terminal *terminal, char *str);
int			ft_tok(t_terminal *terminal, t_tokens **tokens, char *line);
int			ft_loop(t_terminal *terminal, t_tokens **tokens, char **argv);
int			building(t_terminal *terminal, char **envp);
void		built_pwd(void);
int			is_builtin(t_commands	*command);
void		exec_builtin(t_terminal *terminal, t_commands *command, int flag);
void		update_export(t_terminal *terminal);
void		update_exp2(t_terminal *terminal, int i, int j);
int			handle_var(t_commands *command, t_terminal *terminal, int ind);
void		print_var(char *str, t_commands *command);
void		built_echo2(t_commands *command, t_terminal *terminal, int i);

void		clear_sigargs(void);
void		block_signal(void);
void		sig_type(int sig);
void		ctrl_bs(void);
void		ctrl_c(void);
void		signals_main(void);
void		ft_free_tok(t_tokens *tokens);

void		execute(t_commands *cmd, char **env, int tmp);
void		exec(t_terminal *term, t_tokens *tokens);
char		*get_cmd_path(t_commands *com, char **env);
char		**get_path(char **env);
int			ft_strisnb(char *str);
void		built_exit(t_terminal *terminal, t_commands	*command);
int			open_hd(t_commands *command);
char		*get_delim(t_commands *command);
void		fix_command(t_commands *command);
void		reloc_mat(t_commands *command, int ind);
int			exec2(t_terminal *term, t_tokens *tokens, int tmp);
int			exec3(t_terminal *term, t_tokens *tokens, int tmp, int *fd);
int			check3(char *line);
int			check2(char *line, int i);
char		*fix2(char *fixed, char *tmp, int end);

#endif