/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/10 18:38:45 by cmoura-p         ###   ########.fr       */
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
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(SIGNAL_ERROR);
	signal(SIGQUIT, SIG_IGN);
}
