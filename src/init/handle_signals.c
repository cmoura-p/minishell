/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:46:03 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/12 01:45:01 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		g_signal = SIGINT;
		close(STDIN_FILENO);
	}
}

void	heredoc_ctrl_c(t_minishell *bash)
{
	bash->exit_status = EXIT_SIGINT;
	free_to_restart(bash);
	g_signal = 0;
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_ctrl_c(t_minishell *bash)
{
	bash->exit_status = EXIT_SIGINT;
	free_to_restart(bash);
	g_signal = 0;
}

void	handle_ctrl_d(t_minishell *bash)
{
	enum e_exit_code	final_exit_status;

	final_exit_status = bash->exit_status;
	free_bash(bash);
	rl_clear_history();
	ft_printf("exit\n");
	exit(final_exit_status);
}
