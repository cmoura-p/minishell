/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:46:03 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/12 11:28:50 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)	// CTRL+C
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
//		ft_printf(STDOUT_FILENO, "\n");		// AQUI TEM PROBLEMA
		g_signal = SIGINT;
		close(STDIN_FILENO);
	}
}

void	heredoc_ctrl_c(t_minishell *bash)
{
	bash->exit_status = EXIT_SIGINT;
//	free_to_restart(bash);
	g_signal = 0;
}
/* void	heredoc_ctrl_d(t_minishell *bash)
{
//	ft_printf(STDIN_FILENO, "exit\n");
	bash->exit_status = EXIT_SUCCESS;
	free_exit(bash);
}
 */
void	set_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_DFL);
}

