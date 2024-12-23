/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/23 01:10:27 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_prompt(char **prompt)
{
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
		pwd = "erro pwd ";
	*prompt = ft_strjoin(pwd, ": ");
	if (!(*prompt))
		*prompt = pwd;
}
void 	init_data(t_minishell **bash, char **envp, char **prompt)
{
	(void)envp;			// por enquanto

	init_signals();
	get_prompt(prompt);
	*bash = ft_calloc(sizeof(t_minishell), 1);
	if (!(*bash))
		exit(1);
	(*bash)->fd_in = STDIN_FILENO;
	(*bash)->fd_out = STDOUT_FILENO;
}
int	init_bash(t_minishell *minishell, char *prompt)
{
	if (!minishell || !prompt)
		return (0);
	minishell->cmd_line = readline(prompt);
	if (!(minishell->cmd_line))
		return (0);
	add_history(minishell->cmd_line);
	if (!(check_syntax(minishell->cmd_line)))
		return (0);
	return (1);
}

void	init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}
