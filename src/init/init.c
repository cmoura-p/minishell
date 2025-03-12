/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/12 19:31:55 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_minishell	*init_data(char **envp)
{
	t_minishell		*bash;

	init_signals();
	bash = ft_calloc(sizeof(t_minishell), 1);
	if (!bash)
		exit(MALLOC_ERROR);
	bash->fd_in = STDIN_FILENO;
	bash->fd_out = STDOUT_FILENO;
	bash->exit_status = SUCCESS;
	bash->export = NULL;
	bash->heredoc = NULL;
	load_envp(bash, envp);
	load_expo(bash, ft_arraydup(envp));
	return (bash);
}

int	init_bash(t_minishell *minishell)
{
	if (!minishell)
		return (0);
	minishell->cmd_line = readline("minishell42Porto: ");
	if (g_signal == SIGINT)
		handle_ctrl_c(minishell);
	if (!minishell->cmd_line)
		handle_ctrl_d(minishell);
	if ((minishell->cmd_line) && (*(minishell->cmd_line) != '\0'))
	{
		add_history(minishell->cmd_line);
		minishell->cmd_line = ft_minitrim(minishell->cmd_line, 0, 0);
		if ((minishell->cmd_line) && minishell->cmd_line[0] == '\0')
			return (2);
		if (!(check_syntax(minishell->cmd_line)))
		{
			minishell->exit_status = SYNTAX_ERROR;
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		g_signal = SIGINT;
	}
}
