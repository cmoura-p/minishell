/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 20:22:01 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_minishell	*init_data(char **envp, char **prompt)
{
	t_minishell		*bash;

	init_signals();
	get_prompt(prompt);
	bash = ft_calloc(sizeof(t_minishell), 1);
	if (!bash)
		exit(MALLOC_ERROR);
	bash->fd_in = STDIN_FILENO;
	bash->fd_out = STDOUT_FILENO;
	bash->exit_status = SUCCESS;
	bash->export = NULL;
	bash->heredoc = NULL;
	load_envp(bash, envp);
	return (bash);
}

int	init_bash(t_minishell *minishell, char *prompt)
{
	if (!minishell || !prompt)
		return (0);
	minishell->cmd_line = readline(prompt);
	if ((minishell->cmd_line) && (*(minishell->cmd_line) != '\0'))
	{
		add_history(minishell->cmd_line);
		minishell->cmd_line = ft_minitrim(minishell->cmd_line);
		if ((minishell->cmd_line) && minishell->cmd_line[0] == '\0')
			return (2);
		if (!(check_syntax(minishell->cmd_line)))
			return (0);
	}
	else
		return (0);
	return (1);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(SIGNAL_ERROR);
	signal(SIGQUIT, SIG_IGN);
}
